#include <tbs/enc.h>
#include <tbs/log.h>


void _tbs_enc_encrypt(const char *section_start, const char *section_end, tbs_random *random, tbs_crypto_algorithm_initializer crypto_algorithm_init) {
    _TBS_USE_VAR(random);
    _TBS_USE_VAR(crypto_algorithm_init);

    _tbs_log_trace("Encrypt: start=%p end=%p", section_start, section_end);
}

void _tbs_enc_decrypt(const char *section_start, const char *section_end) {
    _tbs_log_trace("Decrypt: start=%p end=%p", section_start, section_end);
}
