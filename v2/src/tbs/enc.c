#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <tbs/enc.h>
#include <tbs/log.h>
#include "platform.h"
#include "checksum.h"

/*
 * The encryption head.
 * TODO: Maybe move to header file.
 */

typedef struct {
    uint8_t encryption_state;
    uint32_t key;
    uint32_t code_length;
} __attribute__((packed)) tbs_enc_head_data;

static_assert(
    sizeof(tbs_enc_head_data) <= _TBS_ENC_HEAD_LEN,
    "Cannot store more data than there is space in the enc_head!"
);

#define TBS_DECRPTED                            (uint8_t)(((uint8_t[])_TBS_ENC_HEAD_OPCODE)[0])

/*
 * Why is the value stored in a temporary variable?
 * Because of a gcc bug:
 * https://stackoverflow.com/questions/18447210/understanding-the-warning-comparison-of-promoted-unsigned-with-unsigned
 */
#define TBS_ENCRYPTED                           ({ const uint8_t _tbs_tmp = ~TBS_DECRPTED; _tbs_tmp; })

/*
 * The encryption foot
 * TODO: Maybe move to header file.
 */

typedef struct {
    const uint8_t foot_marker;
    uint16_t checksum;
} __attribute__((packed)) tbs_enc_foot_data;

static_assert(
    sizeof(tbs_enc_foot_data) <= _TBS_ENC_FOOT_LEN,
    "Cannot store more data than there is space in the enc_foot!"
);

#define TBS_FOOT_MARKER                                         (((uint8_t[])_TBS_ENC_FOOT_OPCODE)[0])




bool _tbs_enc_encrypt(const _tbs_section_location *section, tbs_random *random, tbs_crypto_algorithm_initializer crypto_algorithm_init) {
    tbs_enc_head_data *head = (tbs_enc_head_data *)section->start;
    tbs_enc_foot_data *foot = (tbs_enc_foot_data *)(section->end - _TBS_ENC_FOOT_LEN);
    if (!_TBS_SECTION_IS_DEFINED(*section)) {
        _tbs_log_error("Section is not defined! Do nothing!");
        return false;
    }

    const size_t total_section_size = section->end - section->start;
    _tbs_log_trace("Encrypt: start=%p end=%p", head, foot);

    if (head->encryption_state == TBS_ENCRYPTED) {
        _tbs_log_trace("Section %p is already encrypted", section->start);
        return true;
    }

    if (head->encryption_state != TBS_DECRPTED) {
        _tbs_log_warn("Section %p had an invalid encryption state (expected %02X): %02X", section->start, TBS_DECRPTED, head->encryption_state);
        return false;
    }

    _tbs_log_stringify_memory(section->start, total_section_size, mem, ({
        _tbs_log_trace("Section content before encryption: %s", mem);
    }));

    const uint32_t key = random->next(random);
    tbs_crypto_algorithm crypto_alg;
    crypto_algorithm_init(&crypto_alg, key);
    uint16_t checksum = TBS_CHECKSUM_INIT;

    tbs_page_set_rwx(section->start, total_section_size);
    for (unsigned char *enc_data = section->start + sizeof(*head); enc_data < section->end - _TBS_ENC_FOOT_LEN; ++enc_data) {
        *enc_data = crypto_alg.encrypt(&crypto_alg, *enc_data);
        checksum = tbs_checksum_next(checksum, *enc_data);
    }
    crypto_alg.data_cleanup(&crypto_alg);
    head->encryption_state = TBS_ENCRYPTED;
    head->key = key;
    head->code_length = section->end - section->start - sizeof(*head) - _TBS_ENC_FOOT_LEN;
    foot->checksum = checksum;
    tbs_page_set_rx(section->start, total_section_size);

    _tbs_log_stringify_memory(section->start, total_section_size, mem, ({
        _tbs_log_trace("Section content after encryption: %s", mem);
    }));

    return true;
}

static void tbs_enc_reset_head_opcode(unsigned char *section_head) {
    const unsigned char head_opcode[] = _TBS_ENC_HEAD_OPCODE;
    memcpy(section_head, head_opcode, sizeof(head_opcode));
}

static void tbs_enc_reset_foot_opcode(unsigned char *section_foot) {
    const unsigned char foot_opcode[] = _TBS_ENC_FOOT_OPCODE;
    memcpy(section_foot, foot_opcode, sizeof(foot_opcode));
}

bool _tbs_enc_decrypt(const _tbs_section_location *section, tbs_crypto_algorithm_initializer crypto_algorithm_init) {
    tbs_enc_head_data *head = (tbs_enc_head_data *)section->start;
    tbs_enc_foot_data *foot = (tbs_enc_foot_data *)(section->end - _TBS_ENC_FOOT_LEN);
    if (!_TBS_SECTION_IS_DEFINED(*section)) {
        _tbs_log_error("Section is not defined! Do nothing!");
        return false;
    }

    const size_t code_length = section->end - section->start - sizeof(*head) - _TBS_ENC_FOOT_LEN;
    const size_t total_section_size = section->end - section->start;
    _tbs_log_trace("Decrypt: start=%p end=%p", head, foot);

    if (head->encryption_state == TBS_DECRPTED) {
        _tbs_log_trace("Section %p is already decrypted", section->start);
        return true;
    }

    if (head->encryption_state != TBS_ENCRYPTED) {
        _tbs_log_warn("Section %p had an invalid encryption state (expected %02X): %02X", section->start, TBS_ENCRYPTED, head->encryption_state);
        return false;
    }

    if (head->code_length != code_length) {
        _tbs_log_warn("Section %p has an invalid code length defined", section->start);
        return false;
    }

    _tbs_log_stringify_memory(section->start, total_section_size, mem, ({
        _tbs_log_trace("Section content before decryption: %s", mem);
    }));

    tbs_crypto_algorithm crypto_alg;
    crypto_algorithm_init(&crypto_alg, head->key);
    uint16_t checksum = TBS_CHECKSUM_INIT;

    tbs_page_set_rwx(section->start, total_section_size);
    for (unsigned char *enc_data = section->start + sizeof(*head); enc_data < section->end - _TBS_ENC_FOOT_LEN; ++enc_data) {
        checksum = tbs_checksum_next(checksum, *enc_data);
        *enc_data = crypto_alg.decrypt(&crypto_alg, *enc_data);
    }

    crypto_alg.data_cleanup(&crypto_alg);

    if (checksum != foot->checksum) {
        tbs_page_set_rx(section->end, total_section_size);
        _tbs_log_error("Invalid checksum! Corrupted state!");
        return false;
    }

    tbs_enc_reset_head_opcode((unsigned char *)head);
    tbs_enc_reset_foot_opcode((unsigned char *)foot);

    tbs_page_set_rx(section->end, total_section_size);

    _tbs_log_stringify_memory(section->start, total_section_size, mem, ({
        _tbs_log_trace("Section content after decryption: %s", mem);
    }));

    return false;
}

bool _tbs_detect_decrypted_section_location(_tbs_section_location *result, unsigned char *start_label, unsigned char *end_label) {
    static const unsigned char head_opcode[] = _TBS_ENC_HEAD_OPCODE;
    static const unsigned char foot_opcode[] = _TBS_ENC_FOOT_OPCODE;

    if ((result->start = _tbs_memmem(start_label, end_label, head_opcode, sizeof(head_opcode))) == NULL) {
        _tbs_log_stringify_memory(start_label, end_label - start_label, section, {
            _tbs_log_stringify_memory(head_opcode, sizeof(head_opcode), head_opcode_str, {
                _tbs_log_warn("Could not detect decrypted section start. Section start tag: %s Section: start=%p, end=%p code=%s", head_opcode_str, start_label, end_label, section);
            });
        });
        return false;
    }

    unsigned char *foot_start; 
    if ((foot_start = _tbs_memmem_reversed(result->start + sizeof(head_opcode), end_label, foot_opcode, sizeof(foot_opcode))) == NULL) {
        _tbs_log_stringify_memory(start_label, end_label - start_label, section, {
            _tbs_log_stringify_memory(foot_opcode, sizeof(foot_opcode), foot_opcode_str, {
                _tbs_log_warn("Could not detect section end. Section end tag: %s Section: start=%p, end=%p code=%s", foot_opcode_str, start_label, end_label, section);
            });
        });
        result->start = NULL;
        return false;
    }

    result->end = foot_start + sizeof(foot_opcode);

    _tbs_log_trace("Detected decrypted section start=%p and section end=%p", result->start, result->end);
    return true;
}

bool _tbs_detect_encrypted_section_location(_tbs_section_location *result, unsigned char *start_label, unsigned char *end_label) {
    _TBS_USE_VAR(result);
    _TBS_USE_VAR(start_label);
    _TBS_USE_VAR(end_label);
    /* TODO */
    return false;
}

bool _tbs_detect_section_location(_tbs_section_location *result, unsigned char *start_label, unsigned char *end_label) {
    return _tbs_detect_decrypted_section_location(result, start_label, end_label) || _tbs_detect_encrypted_section_location(result, start_label, end_label);
}

void _tbs_detect_section_location_or_kill(_tbs_section_location *result, unsigned char *start_label, unsigned char *end_label) {
    if (!_tbs_detect_section_location(result, start_label, end_label)) {
        _tbs_log_fatal("Require a section!");
        exit(1);
    }
}