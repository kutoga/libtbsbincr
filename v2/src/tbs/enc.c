#include <stdint.h>
#include <assert.h>
#include <tbs/enc.h>
#include <tbs/log.h>


typedef struct {
    char encryption_state;
    char key[sizeof(uint32_t)];
//    char length[sizeof(uint32_t)];
} __attribute__((packed)) tbs_enc_head;

static_assert(sizeof(tbs_enc_head) == _TBS_ENC_HEAD_LEN, "Invalid tbs_enc_head size!");


// typedef struct {
//     char foot_marker;
//     char checksum[2];
// //    char length[sizeof(uint32_t)];
// } __attribute__((packed)) tbs_enc_foot;

// static_assert(sizeof(tbs_enc_foot) == _TBS_ENC_FOOT_LEN, "Invalid tbs_enc_foot size!");



void _tbs_enc_encrypt(const char *section_start, const char *section_end, tbs_random *random, tbs_crypto_algorithm_initializer crypto_algorithm_init) {
    _TBS_USE_VAR(random);
    _TBS_USE_VAR(crypto_algorithm_init);

    _tbs_log_trace("Encrypt: start=%p end=%p", section_start, section_end);
}

void _tbs_enc_decrypt(const char *section_start, const char *section_end) {
    _tbs_log_trace("Decrypt: start=%p end=%p", section_start, section_end);
}
