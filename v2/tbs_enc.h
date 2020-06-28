#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>

// Base macros

#define _TBS_STMT_WRAPPER(code)                                             \
do { code; } while (0)                                                       \

#define _TBS_STMT_EMPTY                                                     \
_TBS_STMT_WRAPPER()

#define _TBS_STMT_TO_EXPRESSION(stmt)                                       \
({ stmt; NULL; })

#define _TBS_USE_VAR(var)                                                   (void)(var)

#define _TBS_SYM_NAME(n, name)                                             _tbs_ ## n ## __ ## name

#define _TBS_STRUCT_IGNORE_OVERRIDE_EXP(expression)                         \
({                                                                          \
    _Pragma("GCC diagnostic push")                                          \
    _Pragma("GCC diagnostic ignored \"-Wpragmas\"")          \
    _Pragma("GCC diagnostic ignored \"-Wunknown-warning-option\"")          \
    _Pragma("GCC diagnostic ignored \"-Wgnu-designator\"")                  \
    _Pragma("GCC diagnostic ignored \"-Woverride-init\"")                   \
    _Pragma("GCC diagnostic ignored \"-Winitializer-overrides\"") }          \
    const __auto_type _TBS_SYM_NAME(0, ign_ovverride_res) = (expression);                       \
    _Pragma("GCC diagnostic pop")                                          \
    _TBS_SYM_NAME(0, ign_ovverride_res);                                                               \
})


#define _TBS_LABEL(label_name)                                              \
_TBS_STMT_WRAPPER(                                                       \
    label_name:                                                             \
    _TBS_STMT_EMPTY;                                                        \
)

// log

#define _TBS_LOG_PRINTD(file, level, ...)                                   \
_TBS_STMT_WRAPPER(                                                          \
    fprintf((file), "[%30s:%-4d] [%25s] ", __FILE__, __LINE__, __FUNCTION__);\
    fprintf((file), level ": " __VA_ARGS__);                                \
    fputc('\n', (file));                                                    \
    fflush(file);                                                           \
)

#define _tbs_log_trace(...)                                     _TBS_LOG_PRINTD(stdout, "TRACE", __VA_ARGS__)
#define _tbs_log_info(...)                                      _TBS_LOG_PRINTD(stdout, "INFO ", __VA_ARGS__)
#define _tbs_log_warn(...)                                      _TBS_LOG_PRINTD(stderr, "WARN ", __VA_ARGS__)
#define _tbs_log_err(...)                                       _TBS_LOG_PRINTD(stderr, "ERROR", __VA_ARGS__)
#define _tbs_log_fatal(...)                                     _TBS_LOG_PRINTD(stderr, "FATAL", __VA_ARGS__)

// threading

#define _TBS_EXPRESSION_WITH_ACCESS_COUNT(n, enabled, expression, enter_stmt, exit_stmt, if_disabled_init_stmt) \
({                                                          \
    static pthread_mutex_t _TBS_SYM_NAME(n, section_lock) = PTHREAD_MUTEX_INITIALIZER;\
    static unsigned int _TBS_SYM_NAME(n, access_count) = 0;                 \
    if (enabled) {                                                          \
        pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));                \
        if (_TBS_SYM_NAME(n, access_count)++ == 0) {                        \
            enter_stmt;                                                      \
        }                                                                   \
        pthread_mutex_unlock(&_TBS_SYM_NAME(n, section_lock));                \
    } else {                                                                \
        static bool _TBS_SYM_NAME(n, initialized) = false;                  \
        if (!_TBS_SYM_NAME(n, initialized)) {                               \
            pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));            \
            if (!_TBS_SYM_NAME(n, initialized)) {                           \
                _TBS_SYM_NAME(n, initialized) = true;                       \
                if_disabled_init_stmt;                                      \
            }                                                               \
            pthread_mutex_unlock(&_TBS_SYM_NAME(n, section_lock));            \
        }                                                                   \
    }                                                                       \
    const __auto_type _TBS_SYM_NAME(n, access_count_res) = (expression);                \
    if (enabled) {                                                          \
        pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));                \
        if (--_TBS_SYM_NAME(n, access_count) == 0) {                        \
            exit_stmt;                                                       \
        }                                                                   \
        pthread_mutex_unlock(&_TBS_SYM_NAME(n, section_lock));                \
    }                                                                       \
    _TBS_SYM_NAME(n, access_count_res);\
})


// keygen

typedef struct t_tbs_keygen {
    void (*seed)(struct t_tbs_keygen *, int);
    uint16_t (*next)(struct t_tbs_keygen *);
    void (*data_cleanup)(struct t_tbs_keygen *);
    void *data;
} tbs_keygen;

tbs_keygen tbs_keygen_default;

// config

#define _TBS_CONFIG_ENTRIES                                                 \
    bool thread_safe;                                                       \
    bool re_encrypt;                                                        \
    tbs_keygen *keygen;

#define _TBS_CONFIG_DEFAULTS                                                \
    thread_safe:    true,                                                   \
    re_encrypt:     true,                                                   \
    keygen:         &tbs_keygen_default,                                    \

typedef struct {
    _TBS_CONFIG_ENTRIES
} tbs_config;

#define tbs_config_default(...)                                             \
_TBS_STRUCT_IGNORE_OVERRIDE_EXP(((tbs_config) {                             \
    _TBS_CONFIG_DEFAULTS                                                    \
    __VA_ARGS__                                                             \
}))

typedef struct _tbs_section_config {
    _TBS_CONFIG_ENTRIES
    const tbs_config *settings;
} _tbs_section_config;

#define _TBS_SECTION_CONFIG_DEFAULTS                                        \
    _TBS_CONFIG_DEFAULTS                                                    \
    settings: NULL,

#define _TBS_SECTION_CONFIG_DEFAULT(...)                                    \
_TBS_STRUCT_IGNORE_OVERRIDE_EXP(((_tbs_section_config) {                    \
    _TBS_SECTION_CONFIG_DEFAULTS                                            \
    __VA_ARGS__                                                             \
}))

#define _TBS_SECTION_CONFIG_GET(config, key)                                \
(config.settings ? config.settings->key : config.key)

// tbs_enc_macros

#define _TBS_ENC_EXP(n, expression, ...)                                              \
({                                                          \
    const _tbs_section_config _TBS_SYM_NAME(n, config) =                    \
        _TBS_SECTION_CONFIG_DEFAULT(__VA_ARGS__);                           \
        (void)&&_TBS_SYM_NAME(n, section_start);\
        (void)&&_TBS_SYM_NAME(n, section_end);\
    _TBS_EXPRESSION_WITH_ACCESS_COUNT(                                         \
        n,                                                                  \
        _TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), thread_safe) &&   \
        _TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), re_encrypt),      \
        {                                                  \
            _TBS_LABEL(_TBS_SYM_NAME(n, section_start));                    \
            const __auto_type _TBS_SYM_NAME(n, enc_exp_res) = (expression);                                                           \
            _tbs_log_trace("code done");\
            _TBS_LABEL(_TBS_SYM_NAME(n, section_end));                      \
            _TBS_SYM_NAME(n, enc_exp_res);\
        },                                                                  \
        _TBS_STMT_WRAPPER(                                                  \
            /* decrypt */                                                   \
            _tbs_log_trace("decrypt");\
        ),                                                                  \
        _TBS_STMT_WRAPPER(                                                  \
            /* encrypt */                                                   \
            _tbs_log_trace("encrypt");\
        ),                                                                  \
        _TBS_STMT_WRAPPER(                                                  \
            /* descrypt */                                                  \
            _tbs_log_trace("init decrypt");\
        )                                                                   \
    );                                                                       \
})


#define tbs_enc(code, ...)                                                  \
_TBS_STMT_WRAPPER(_TBS_ENC_EXP(__COUNTER__, ({ _TBS_STMT_WRAPPER(code); NULL; }), __VA_ARGS__))

#define tbs_enc_exp(expression, ...) \
_TBS_ENC_EXP(__COUNTER__, (expression), __VA_ARGS__)
