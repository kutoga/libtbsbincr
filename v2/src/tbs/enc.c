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

#define TBS_DECRPTED                            (((uint8_t[])_TBS_ENC_HEAD_OPCODE)[0])

/*
 * Why is the value stored in a temporary variable?
 * Because of a gcc bug:
 * https://stackoverflow.com/questions/18447210/understanding-the-warning-comparison-of-promoted-unsigned-with-unsigned
 */
#define TBS_ENCRYPTED                           ({ const __auto_type _tbs_tmp = ~TBS_DECRPTED; _tbs_tmp; })

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
    tbs_enc_foot_data *foot = (tbs_enc_foot_data *)(section->end - sizeof(tbs_enc_foot_data));
    const size_t total_section_size = section->end - section->start;
    _tbs_log_trace("Encrypt: start=%p end=%p", head, foot);
    _tbs_log_stringify_memory(section->start, total_section_size, mem, ({
        _tbs_log_trace("Section content: %s", mem);
    }));

    if (head->encryption_state == TBS_ENCRYPTED) {
        _tbs_log_trace("Section %p is already encrypted", section->start);
        return true;
    }

    if (head->encryption_state != TBS_DECRPTED) {
        _tbs_log_warn("Section %p had an invalid encryption state: %x", section->start, head->encryption_state);
        return false;
    }

    const uint32_t key = random->next(random);
    tbs_crypto_algorithm crypto_alg;
    crypto_algorithm_init(&crypto_alg, key);
    uint16_t checksum = TBS_CHECKSUM_INIT;

    tbs_page_set_rwx(section->start, total_section_size);
    for (unsigned char *enc_data = section->start + sizeof(*head); enc_data < section->end - sizeof(*foot); ++enc_data) {
        *enc_data = crypto_alg.encrypt(&crypto_alg, *enc_data);
        checksum = tbs_checksum_next(checksum, *enc_data);
    }
    tbs_page_set_rx(section->start, total_section_size);

    crypto_alg.data_cleanup(&crypto_alg);

    head->encryption_state = TBS_ENCRYPTED;
    head->key = key;
    head->code_length = section->end - section->start - sizeof(*head) - sizeof(*foot);
    foot->checksum = checksum;

    return true;
}

static void tbs_enc_reset_head_opcode(unsigned char *section_head) {
    const char head_opcode[] = _TBS_ENC_HEAD_OPCODE;
    memcpy(section_head, head_opcode, sizeof(head_opcode));
}

static void tbs_enc_reset_foot_opcode(unsigned char *section_foot) {
    const char foot_opcode[] = _TBS_ENC_FOOT_OPCODE;
    memcpy(section_foot, foot_opcode, sizeof(foot_opcode));
}

bool _tbs_enc_decrypt(const _tbs_section_location *section, tbs_crypto_algorithm_initializer crypto_algorithm_init) {
    tbs_enc_head_data *head = (tbs_enc_head_data *)section->start;
    tbs_enc_foot_data *foot = (tbs_enc_foot_data *)(section->end - sizeof(tbs_enc_foot_data));
    const size_t code_length = section->end - section->start - sizeof(*head) - sizeof(*foot);
    const size_t total_section_size = section->end - section->start;
    _tbs_log_trace("Decrypt: start=%p end=%p", head, foot);
    _tbs_log_stringify_memory(section->start, total_section_size, mem, ({
        _tbs_log_trace("Section content: %s", mem);
    }));

    if (head->encryption_state == TBS_DECRPTED) {
        _tbs_log_trace("Section %p is already decrypted", section->start);
        return true;
    }

    if (head->encryption_state != TBS_ENCRYPTED) {
        _tbs_log_warn("Section %p had an invalid encryption state: %x", section->start, head->encryption_state);
        return false;
    }

    if (head->code_length != code_length) {
        _tbs_log_warn("Section %p has an invalid code length defined", section->start);
        return false;
    }

    tbs_crypto_algorithm crypto_alg;
    crypto_algorithm_init(&crypto_alg, head->key);
    uint16_t checksum = TBS_CHECKSUM_INIT;

    tbs_page_set_rwx(section->start, total_section_size);
    for (unsigned char *enc_data = section->start + sizeof(*head); enc_data < section->end - sizeof(*foot); ++enc_data) {
        checksum = tbs_checksum_next(checksum, *enc_data);
        *enc_data = crypto_alg.decrypt(&crypto_alg, *enc_data);
    }
    tbs_page_set_rx(section->end, total_section_size);

    crypto_alg.data_cleanup(&crypto_alg);

    if (checksum != foot->checksum) {
        _tbs_log_error("Invalid checksum! Corrupted state!");
        return false;
    }

    tbs_enc_reset_head_opcode(section->start);
    tbs_enc_reset_foot_opcode(section->end - sizeof(*foot));

    return false;
}

bool _tbs_detect_section_location(_tbs_section_location *result, unsigned char *start_label, unsigned char *end_label) {
    static const unsigned char head_opcode[] = _TBS_ENC_HEAD_OPCODE;
    static const unsigned char foot_opcode[] = _TBS_ENC_FOOT_OPCODE;

    if ((result->start = _tbs_memmem(start_label, end_label, head_opcode, sizeof(head_opcode))) == NULL) {
        _tbs_log_stringify_memory(start_label, end_label - start_label, section, {
            _tbs_log_stringify_memory(head_opcode, sizeof(head_opcode), head_opcode_str, {
                _tbs_log_error("Could not detect section start. Section start tag: %s Section: %s", head_opcode_str, section);
            });
        });
        return false;
    }

    if ((result->end = _tbs_memmem_reversed(start_label, end_label, foot_opcode, sizeof(foot_opcode))) == NULL) {
        _tbs_log_stringify_memory(start_label, end_label - start_label, section, {
            _tbs_log_stringify_memory(foot_opcode, sizeof(foot_opcode), foot_opcode_str, {
                _tbs_log_error("Could not detect section end. Section end tag: %s Section: %s", foot_opcode_str, section);
            });
        });
        return false;
    }

    _tbs_log_trace("Detected section start=%p and section end=%p", result->start, result->end);
    return true;
}
