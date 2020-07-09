#include <stdint.h>
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

#define TBS_ENCRYPTED                           (((uint8_t[])_TBS_ENC_HEAD_OPCODE)[0])

/*
 * Why is the value stored in a temporary variable?
 * Because of a gcc bug:
 * https://stackoverflow.com/questions/18447210/understanding-the-warning-comparison-of-promoted-unsigned-with-unsigned
 */
#define TBS_DECRPTED                            ({ const __auto_type _tbs_tmp = ~TBS_ENCRYPTED; _tbs_tmp; })

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




bool _tbs_enc_encrypt(char *section_head, char *section_foot, tbs_random *random, tbs_crypto_algorithm_initializer crypto_algorithm_init) {
    tbs_enc_head_data *head = (tbs_enc_head_data *)section_head;
    tbs_enc_foot_data *foot = (tbs_enc_foot_data *)section_foot;
    size_t total_section_size = section_head - section_foot + sizeof(foot);
    _tbs_log_trace("Encrypt: start=%p end=%p", head, foot);

    if (head->encryption_state == TBS_ENCRYPTED) {
        _tbs_log_trace("Section %p is already encrypted", section_head);
        return true;
    }

    if (head->encryption_state != TBS_DECRPTED) {
        _tbs_log_warn("Section %p had an invalid encryption state: %x", section_head, head->encryption_state);
        return false;
    }

    const uint32_t key = random->next(random);
    tbs_crypto_algorithm crypto_alg;
    crypto_algorithm_init(&crypto_alg, key);
    uint16_t checksum = TBS_CHECKSUM_INIT;

    tbs_page_set_rwx(section_head, total_section_size);
    for (char *enc_data = section_head + sizeof(*head); enc_data < section_foot; ++enc_data) {
        *enc_data = crypto_alg.encrypt(&crypto_alg, *enc_data);
        checksum = tbs_checksum_next(checksum, *enc_data);
    }
    tbs_page_set_rx(section_head, total_section_size);

    crypto_alg.data_cleanup(&crypto_alg);

    // TODO: Update head / foot

    return true;
}

bool _tbs_enc_decrypt(char *section_head, char *section_foot) {
    tbs_enc_head_data *head = (tbs_enc_head_data *)section_head;
    tbs_enc_foot_data *foot = (tbs_enc_foot_data *)section_foot;
    _tbs_log_trace("Decrypt: start=%p end=%p", head, foot);

    if (head->encryption_state == TBS_DECRPTED) {
        _tbs_log_trace("Section %p is already decrypted", section_head);
        return true;
    }

    if (head->encryption_state != TBS_ENCRYPTED) {
        _tbs_log_warn("Section %p had an invalid encryption state: %x", section_head, head->encryption_state);
        return false;
    }

    return false;
}
