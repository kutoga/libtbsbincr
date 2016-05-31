#ifndef __TBS_ENCR_CORE_H__
#define __TBS_ENCR_CORE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <tbs/bincr/minimal.h>
#include <tbs/bincr/keygen.h>

int tbs_bincr_generate_file_seed(FILE *file);

int tbs_bincr_generate_section_seed(void *section, void *end_flag);

uint16_t tbs_bincr_generate_key(void *section, void *end_flag);

int tbs_bincr_encrypt(void *section, void *end_flag, uint16_t key, int change_access_rights);

int tbs_bincr_encrypt_file(FILE *file, tbs_bincr_key_gen_t *key_gen);

int tbs_bincr_decrypt_file(FILE *file);

int tbs_bincr_reencrypt_file(FILE *file, tbs_bincr_key_gen_t *key_gen);

int tbs_bincr_reencrypt_file_seed(FILE *file, tbs_bincr_key_gen_t *key_gen, int additional_seed);

#ifdef TBS_BINCR_DISABLE
#define tbs_enc_encrypt_n(n)                                TBS_UTIL_STATEMENT_EMPTY
#define tbs_enc_gen_key_n(n)                                0
#else
#define tbs_enc_encrypt_n(n, k)                             \
TBS_UTIL_STATEMENT_WRAPPER(                                 \
    if (TBS_BINCR_IS_DECRYPTED(*((unsigned const char *)    \
        &&TBS_BINCR_VAR_BEGIN(n)))) {                       \
        tbs_bincr_encrypt(                                  \
            &&TBS_BINCR_VAR_BEGIN(n),                       \
            &&TBS_BINCR_VAR_END(n),                         \
            (k), 1                                          \
        );                                                  \
    }                                                       \
)
#define tbs_enc_gen_key_n(n)                                tbs_bincr_generate_key(&&TBS_BINCR_VAR_BEGIN(n), &&TBS_BINCR_VAR_END(n))
#endif

#define tbs_enc_gen_key()                                   tbs_enc_gen_key_n(TBS_ENC_DEFAULT_N)
#define tbs_enc_encrypt(k)                                  tbs_enc_encrypt_n(TBS_ENC_DEFAULT_N, (k))

/* Provide some threaded macros */
#define tbs_enc_encrypt_nt(n)                               \
TBS_ENC_LOCK_DEC(n,                                         \
    if (TBS_BINCR_VAR_LOCK_COUNT(n) == 0) {                 \
        tbs_enc_encrypt_n(n, TBS_BINCR_VAR_LOCK_KEY(n));    \
    }                                                       \
)
#define tbs_enc_encrypt_t()                                 tbs_enc_encrypt_nt(TBS_ENC_DEFAULT_N)

#define tbs_enc_code_ft_n(n, code)                          \
TBS_UTIL_STATEMENT_WRAPPER(                                 \
    tbs_enc_threaded_n(n);                                  \
    tbs_enc_decrypt_nt(n, tbs_enc_gen_key_n(n));            \
    tbs_enc_code_nt(n, code);                               \
    tbs_enc_encrypt_nt(n);                                  \
)
#define tbs_enc_code_ft(code)                               tbs_enc_code_ft_n(TBS_ENC_DEFAULT_N, code)

#define tbs_enc_proc_t(code)                                { tbs_enc_code_ft(code); }

#ifdef __cplusplus
}
#endif

#endif /* __TBS_ENCR_CORE_H__ */
