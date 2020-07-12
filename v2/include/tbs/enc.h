#ifndef __TBS_ENC_H__
#define __TBS_ENC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>
#include "common.h"
#include "log.h"
#include "config.h"
#include "asm.h"

/*
 * Define an expression which is protected. This means before it is
 * accessed some code has to be executed and after the expression is
 * evaluated another piece of code is executed.
 * 
 * This macro can do this re_enetrant (evaluation the expression
 * multiple times; e.g. recursive), thread safe and auto reset the
 * state. If auto reset is disabled, the exit expression is never
 * executed.
 * 
 * Notice: Given the parameters are known at compile time, most of
 * the generated code will be optimized away. Therefore, if possible,
 * it is recommended to pass compile-time constants.
 * 
 * Parameters:
 * n            A unique identifer number; is used for variables etc.
 * expression   The protected expression
 * re_enetrant  Support recursive calls; also parallel calls, but in
 *              this case "thread_safe" should also be set
 * thread_safe  Allow it to use multiple threads to evaluate the expression
 *              at the same time.
 * auto_reset   If not set, the prepare_stmt will be executed once and the
 *              reset_stmt never.
 * prepare_stmt Before the expression is evaluated, this statement is
 *              executed.
 * reset_stmt   After the expression is evaluated, this statement is
 *              executed.
 */
#define _TBS_PROTECTED_EXPRESSION(                                          \
    n,                                                                      \
    expression,                                                             \
                                                                            \
    re_enetrant,                                                            \
    thread_safe,                                                            \
    auto_reset,                                                             \
                                                                            \
    prepare_stmt,                                                           \
    reset_stmt                                                              \
)                                                                           \
({                                                                          \
    static pthread_mutex_t _TBS_SYM_NAME(n, section_lock) =                 \
        PTHREAD_MUTEX_INITIALIZER;                                          \
    static int _TBS_SYM_NAME(n, access_count) = 0;                          \
    if (!auto_reset) {                                                      \
        static bool _TBS_SYM_NAME(n, initialized) = false;                  \
        if (!_TBS_SYM_NAME(n, initialized)) {                               \
            if (thread_safe) {                                              \
                pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));        \
            }                                                               \
            if (!_TBS_SYM_NAME(n, initialized)) {                           \
                _TBS_SYM_NAME(n, initialized) = true;                       \
                prepare_stmt;                                               \
            }                                                               \
            if (thread_safe) {                                              \
                pthread_mutex_unlock(&_TBS_SYM_NAME(n, section_lock));      \
            }                                                               \
        }                                                                   \
    } else if (re_enetrant) {                                               \
        if (thread_safe) {                                                  \
            pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));            \
        }                                                                   \
        if (_TBS_SYM_NAME(n, access_count)++ == 0) {                        \
            prepare_stmt;                                                   \
        }                                                                   \
        if (thread_safe) {                                                  \
            pthread_mutex_unlock(&_TBS_SYM_NAME(n, section_lock));          \
        }                                                                   \
    } else if (thread_safe) {                                               \
        pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));                \
        prepare_stmt;                                                       \
    }                                                                       \
    const _tbs_auto_type _TBS_SYM_NAME(n, protected_exp_res) = (expression);   \
    if (auto_reset) {                                                       \
        if (re_enetrant) {                                                  \
            if (thread_safe) {                                              \
                pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));        \
            }                                                               \
            if (_TBS_SYM_NAME(n, access_count)++ == 0) {                    \
                reset_stmt;                                                 \
            }                                                               \
            if (thread_safe) {                                              \
                pthread_mutex_unlock(&_TBS_SYM_NAME(n, section_lock));      \
            }                                                               \
        } else if (thread_safe) {                                           \
            reset_stmt;                                                     \
            pthread_mutex_unlock(&_TBS_SYM_NAME(n, section_lock));          \
        }                                                                   \
    }                                                                       \
    _TBS_SYM_NAME(n, protected_exp_res);                                    \
})


typedef struct _tbs_section_location {
    unsigned char *start;
    unsigned char *end;
} _tbs_section_location;

#define _TBS_SECTION_IS_DEFINED(section)                                    ((section).start != NULL)

bool _tbs_detect_section_location(_tbs_section_location *result, unsigned char *start_label, unsigned char *end_label);

bool _tbs_enc_encrypt(const _tbs_section_location *section, tbs_random *random, tbs_crypto_algorithm_initializer crypto_algorithm_init);

bool _tbs_enc_decrypt(const _tbs_section_location *section, tbs_crypto_algorithm_initializer crypto_algorithm_init);

/*
 * Encrypt a given expression.
 * 
 * Parameters:
 * n            A unique identifer number; is used for variables etc.
 * expression   The expression to encrypt.
 * ...          Config parameters; if not given, the default configuration
 *              is used.
 */
#define _TBS_ENC_EXP(n, expression, ...)                                    \
({                                                                          \
    __label__ _TBS_SYM_NAME(n, section_start);                              \
    __label__ _TBS_SYM_NAME(n, section_end);                                \
    const _tbs_section_config _TBS_SYM_NAME(n, config) =                    \
        _TBS_SECTION_CONFIG_DEFAULT(__VA_ARGS__);                           \
    static _tbs_section_location _TBS_SYM_NAME(n, section_location) = { .start = NULL, .end = NULL }; \
    if (!_TBS_SECTION_IS_DEFINED(_TBS_SYM_NAME(n, section_location))) {     \
        if (_TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), thread_safe)) {   \
            static pthread_mutex_t _TBS_SYM_NAME(n, section_detection_lock) =                 \
                PTHREAD_MUTEX_INITIALIZER;                                      \
            pthread_mutex_lock(&_TBS_SYM_NAME(n, section_detection_lock));      \
            if (!_TBS_SECTION_IS_DEFINED(_TBS_SYM_NAME(n, section_location))) { \
                /* detect */                                                    \
                _tbs_detect_section_location(                                   \
                    &_TBS_SYM_NAME(n, section_location),                 \
                    (unsigned char *)&&_TBS_SYM_NAME(n, section_start),         \
                    (unsigned char *)&&_TBS_SYM_NAME(n, section_end));           \
            }                                                                       \
            pthread_mutex_unlock(&_TBS_SYM_NAME(n, section_detection_lock));        \
        } else {                                                                    \
                /* detect */                                                                \
                _tbs_detect_section_location(                                   \
                    &_TBS_SYM_NAME(n, section_location),                 \
                    (unsigned char *)&&_TBS_SYM_NAME(n, section_start),         \
                    (unsigned char *)&&_TBS_SYM_NAME(n, section_end));           \
        }                                                                       \
    }                                                                       \
    _TBS_PROTECTED_EXPRESSION(                                              \
        n,                                                                  \
        ({                                                                  \
                                \
            _TBS_AVOID_LABEL_OPTIMIZATIONS({_TBS_LABEL(_TBS_SYM_NAME(n, section_start));_TBS_ENC_HEAD_ASM;});            \
                                                                            \
            const _tbs_auto_type _TBS_SYM_NAME(n, enc_exp_res) = (expression); \
            _tbs_log_trace("code done");                                    \
                                                                            \
                                  \
            _TBS_ENC_FOOT_ASM;  \
            _TBS_AVOID_LABEL_OPTIMIZATIONS(_TBS_LABEL(_TBS_SYM_NAME(n, section_end)));            \
                                                                            \
            _TBS_SYM_NAME(n, enc_exp_res);                                  \
        }),                                                                 \
        _TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), re_enetrant),     \
        _TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), thread_safe),     \
        _TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), re_encrypt),      \
        _TBS_STMT_WRAPPER(                                                  \
            _tbs_enc_decrypt(                                               \
                &_TBS_SYM_NAME(n, section_location),                           \
                _TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), crypto_algorithm_init)); \
        ),                                                                  \
        _TBS_STMT_WRAPPER(                                                  \
            _tbs_enc_encrypt(                                               \
                &_TBS_SYM_NAME(n, section_location),                           \
                _TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), keygen),  \
                _TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), crypto_algorithm_init)); \
        )                                                                   \
    );                                                                      \
})

/*
 * The library interface:
 * tbs_enc and tbc_enc_exp
 */
#ifndef TBS_ENC_DISABLE

#define tbs_enc(code, ...)                                                  \
_TBS_STMT_WRAPPER(_TBS_ENC_EXP(__COUNTER__, ({                              \
    _TBS_STMT_WRAPPER(code);                                                \
    NULL;                                                                   \
}), __VA_ARGS__))
#define tbs_enc_exp(expression, ...)                                        _TBS_ENC_EXP(__COUNTER__, (expression), __VA_ARGS__)

#else

#define tbs_enc(code, ...)                                                  _TBS_STMT_WRAPPER(code)
#define tbs_enc_exp(expression, ...)                                        (expression)

#endif


#ifdef __cplusplus
}
#endif

#endif
