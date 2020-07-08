#include <stdint.h>
#include <assert.h>
#include <tbs/enc.h>
#include <tbs/log.h>

typedef struct {
    uint8_t encryption_state;
    uint32_t key;
    uint32_t length;
} __attribute__((packed)) tbs_enc_head_data;

static_assert(
    sizeof(tbs_enc_head_data) <= _TBS_ENC_HEAD_LEN,
    "Cannot store more data than there is space in the enc_head!"
);

#define TBS_ENCRYPTED                           (((uint8_t[])_TBS_ENC_HEAD_OPCODE)[0])
#define TBS_DECRPTED                            (~TBS_ENCRYPTED)


typedef struct {
    const uint8_t foot_marker;
    uint16_t checksum;
} __attribute__((packed)) tbs_enc_foot_data;

static_assert(
    sizeof(tbs_enc_foot_data) <= _TBS_ENC_FOOT_LEN,
    "Cannot store more data than there is space in the enc_foot!"
);

#define TBS_FOOT_MARKER                         (((uint8_t[])_TBS_ENC_FOOT_OPCODE)[0])


void _tbs_enc_encrypt(const char *section_start, const char *section_end, tbs_random *random, tbs_crypto_algorithm_initializer crypto_algorithm_init) {
    _TBS_USE_VAR(random);
    _TBS_USE_VAR(crypto_algorithm_init);

    _tbs_log_trace("Encrypt: start=%p end=%p", section_start, section_end);
}

void _tbs_enc_decrypt(const char *section_start, const char *section_end) {
    _tbs_log_trace("Decrypt: start=%p end=%p", section_start, section_end);
}
