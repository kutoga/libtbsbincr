#ifndef __TBS_BINCR_MINIMAL_H__
#define __TBS_BINCR_MINIMAL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <tbs/util.h>
#include <tbs/log/core.h>

#if 0
#define TBS_BINCR_DISABLE
#define TBS_BINCR_DISABLE_LIBENC
#endif

static inline void __attribute__((always_inline)) TBS_BINCR_ENC_HEAD() {
    __asm__ __volatile__(
#if __x86_64__
        ".code64\n\t"
        "push %rax\n\t"
        "push %rax\n\t"
        "nop\n\t"
        "pop %rax\n\t"
        "pop %rax\n\t"
#else
        ".code32\n\t"
        "push %eax\n\t"
        "push %eax\n\t"
        "nop\n\t"
        "pop %eax\n\t"
        "pop %eax\n\t"
#endif
    );
}

static inline void __attribute__((always_inline)) TBS_BINCR_ENC_FOOT() {
    __asm__ __volatile__(
#if __x86_64__
        ".code64\n\t"
        "push %rbx\n\t"
        "push %rbx\n\t"
        "nop\n\t"
        "pop %rbx\n\t"
        "pop %rbx\n\t"
#else
        ".code32\n\t"
        "push %ebx\n\t"
        "push %ebx\n\t"
        "nop\n\t"
        "pop %ebx\n\t"
        "pop %ebx\n\t"
#endif
    );
}

/*
 * TODO: Autogenerate (currently used: https://defuse.ca/online-x86-assembler.htm#disassembly ) 
 * Fortunately the code is exactely the same for 32 and 64 bit:)
 */
#define TBS_BINCR_ENC_HEAD_OPCODE                           { 0x50, 0x50, 0x90, 0x58, 0x58 }
#define TBS_BINCR_ENC_FOOT_OPCODE                           { 0x53, 0x53, 0x90, 0x5B, 0x5B }
#define TBS_BINCR_ENC_HEAD_OPCODE_ARR                       ((unsigned char[])TBS_BINCR_ENC_HEAD_OPCODE)
#define TBS_BINCR_ENC_FOOT_OPCODE_ARR                       ((unsigned char[])TBS_BINCR_ENC_FOOT_OPCODE)

#define TBS_BINCR_DECRYPTED                                 (TBS_BINCR_ENC_HEAD_OPCODE_ARR[0])
#define TBS_BINCR_ENCRYPTED                                 (TBS_BINCR_DECRYPTED ^ (unsigned char)0xFF)

#define TBS_BINCR_IS_DECRYPTED(c)                           ((unsigned char)(c) == TBS_BINCR_DECRYPTED)
#define TBS_BINCR_IS_ENCRYPTED(c)                           ((unsigned char)(c) == TBS_BINCR_ENCRYPTED)

static inline unsigned char __attribute__((always_inline)) tbs_bincr_next_key_byte(uint16_t *key) {

    /*
     * This cipher is very minimal and bad. The encryption is easy to hack, but it doesnt has to be very good.
     * It just should hide the code. In later releases it could be improved (probably not).
     */
     
    /* Based on http://stackoverflow.com/a/11946674/916672 */
    *key = (uint16_t)(((uint32_t)*key) * (uint32_t)1103515245U + 12345U);
    return (unsigned char)*key;
}

const unsigned char *tbs_bincr_enc_head_opcode(void);

const unsigned char *tbs_bincr_enc_foot_opcode(void);

int tbs_bincr_decrypt(void *section, int change_access_rights);

#define TBS_BINCR_VAR(pr, name)                             __lib_encrypt_ ## pr ## __ ## name ## __

#define TBS_BINCR_VAR_BEGIN(n)                              TBS_BINCR_VAR(n, begin)
#define TBS_BINCR_VAR_END(n)                                TBS_BINCR_VAR(n, end)

#ifdef TBS_BINCR_DISABLE
#define tbs_enc_decrypt_n(n)                                TBS_UTIL_STATEMENT_EMPTY()
#define tbs_enc_code_n(n, code)                             TBS_UTIL_STATEMENT_WRAPPER(code)
#define tbs_enc_stmt_n(stmt)                                (stmt)
#else
#define tbs_enc_decrypt_n(n)                                \
TBS_UTIL_STATEMENT_WRAPPER(                                 \
    unsigned const char *TBS_BINCR_VAR(n, head) =           \
        (unsigned const char *)&&TBS_BINCR_VAR_BEGIN(n);    \
    if (TBS_BINCR_IS_ENCRYPTED(*TBS_BINCR_VAR(n, head))) {  \
        tbs_bincr_decrypt(&&TBS_BINCR_VAR_BEGIN(n), 1);     \
    }                                                       \
)
#define tbs_enc_code_nt(n, code)                            \
TBS_UTIL_STATEMENT_WRAPPER(                                 \
    TBS_BINCR_VAR_BEGIN(n):                                 \
    TBS_BINCR_ENC_HEAD();                                   \
                                                            \
    /* This line is needed for void functions.  */          \
    /* Otherwise 'dead' code would be removed.  */          \
    /* In general this if-statement is useless. */          \
    if (*((char *)&&TBS_BINCR_VAR_END(n))) { code }         \
                                                            \
    TBS_BINCR_VAR_END(n):                                   \
    TBS_BINCR_ENC_FOOT();                                   \
)
#define tbs_enc_code_n(n, code)                             \
TBS_UTIL_STATEMENT_WRAPPER(                                 \
    tbs_enc_decrypt_n(n);                                   \
    tbs_enc_code_nt(n, code);                               \
)
#define tbs_enc_stmt_n(n, stmt)                             \
({                                                          \
    typeof(stmt) TBS_BINCR_VAR(n, stmt_res) = { 0 };        \
    tbs_enc_code_n(n,                                       \
        TBS_BINCR_VAR(n, stmt_res) = (stmt);                \
    );                                                      \
    TBS_BINCR_VAR(n, stmt_res);                             \
})

#endif

#define TBS_ENC_DEFAULT_N                                   __TBS__DEFAULT_N__
#define tbs_enc_code(code)                                  tbs_enc_code_n(TBS_ENC_DEFAULT_N, code)
#define tbs_enc_proc(code)                                  { tbs_enc_code(code); }
#define tbs_enc_decrypt()                                   tbs_enc_decrypt_n(TBS_ENC_DEFAULT_N)
#define tbs_enc_stmt(stmt)                                  tbs_enc_stmt_n(TBS_ENC_DEFAULT_N, (stmt))

/* Provide some thread options. */
#define tbs_enc_code_t(code)                                tbs_enc_code_nt(TBS_ENC_DEFAULT_N, code)
#define TBS_BINCR_VAR_LOCK(n)                               TBS_BINCR_VAR(n, lock)
#define TBS_BINCR_VAR_LOCK_INIT(n)                          TBS_BINCR_VAR(n, lock_init)
#define TBS_BINCR_VAR_LOCK_COUNT(n)                         TBS_BINCR_VAR(n, lock_count)
#define TBS_BINCR_VAR_LOCK_KEY(n)                           TBS_BINCR_VAR(n, lock_key)

#define tbs_enc_threaded_n(n)                               \
static TBS_UTIL_MUTEX_T TBS_BINCR_VAR_LOCK(n);              \
static int TBS_BINCR_VAR_LOCK_INIT(n) = 0;                  \
static unsigned int TBS_BINCR_VAR_LOCK_COUNT(n) = 0;        \
static uint16_t TBS_BINCR_VAR_LOCK_KEY(n) = 0;              \
if (!TBS_BINCR_VAR_LOCK_INIT(n)) {                          \
    TBS_UTIL_MUTEX_INIT(&TBS_BINCR_VAR_LOCK(n));            \
}                                                           \
TBS_UTIL_USE_VAR(TBS_BINCR_VAR_LOCK_COUNT(n));              \
TBS_UTIL_USE_VAR(TBS_BINCR_VAR_LOCK_KEY(n))

#define tbs_enc_threaded()                                  tbs_enc_threaded_n(TBS_ENC_DEFAULT_N)

#define TBS_ENC_LOCK_N(n)                                   TBS_UTIL_MUTEX_LOCK(&TBS_BINCR_VAR_LOCK(n))
#define TBS_ENC_UNLOCK_N(n)                                 TBS_UTIL_MUTEX_UNLOCK(&TBS_BINCR_VAR_LOCK(n))
#define TBS_ENC_LOCKED(n, code)                             \
TBS_UTIL_STATEMENT_WRAPPER(                                 \
    TBS_ENC_LOCK_N(n);                                      \
    code                                                    \
    TBS_ENC_UNLOCK_N(n);                                    \
)
#define TBS_ENC_LOCK_INC(n, code)                           \
TBS_ENC_LOCKED(n,                                           \
    TBS_BINCR_VAR_LOCK_COUNT(n)++;                          \
    tbs_log_trace("Incremented lock count for '" #n "': %d",\
        TBS_BINCR_VAR_LOCK_COUNT(n));                       \
    code                                                    \
)
#define TBS_ENC_LOCK_DEC(n, code)                           \
TBS_ENC_LOCKED(n,                                           \
    TBS_BINCR_VAR_LOCK_COUNT(n)--;                          \
    tbs_log_trace("Decremented lock count for '" #n "': %d",\
        TBS_BINCR_VAR_LOCK_COUNT(n));                       \
    code                                                    \
)
#define tbs_enc_decrypt_nt(n, k)                            \
TBS_ENC_LOCK_INC(n,                                         \
    if (TBS_BINCR_VAR_LOCK_COUNT(n) == 1) {                 \
        TBS_BINCR_VAR_LOCK_KEY(n) = (k);                    \
        tbs_enc_decrypt_n(n);                               \
    }                                                       \
)
#define tbs_enc_decrypt_t(k)                                tbs_enc_decrypt_nt(TBS_ENC_DEFAULT_N, (k))


#ifdef __cplusplus
}
#endif

#endif /* __TBS_BINCR_MINIMAL_H__ */


