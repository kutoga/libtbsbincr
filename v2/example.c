#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

// Base macros

#define _TBS_STMT_WRAPPER(code)                                             \
do { code } while (0)                                                       \

#define _TBS_STMT_EMPTY                                                     \
_TBS_STMT_WRAPPER()

#define _TBS_STMT_TO_EXPRESSION(stmt)                                       \
({ stmt; NULL; })

#define _TBS_USE_VAR(var)                                                   (void)(var)

#define _TBS_STRUCT_IGNORE_OVERRIDE_EXP(expression)                         \
({                                                                          \
    _Pragma("GCC diagnostic push")                                          \
    _Pragma("GCC diagnostic ignored \"-Wpragmas\"")          \
    _Pragma("GCC diagnostic ignored \"-Wunknown-warning-option\"")          \
    _Pragma("GCC diagnostic ignored \"-Wgnu-designator\"")                  \
    _Pragma("GCC diagnostic ignored \"-Woverride-init\"")                   \
    _Pragma("GCC diagnostic ignored \"-Winitializer-overrides\"")           \
    const typeof(expression) _tbs_res = (expression);                       \
    _Pragma("GCC diagnostic pop")                                           \
    _tbs_res;                                                               \
})

#define _TBS_SYM_NAME(n, name)                                             _tbs_ ## n ## __ ## name

#define _TBS_LABEL(label_name)                                              \
_TBS_STMT_WRAPPER(                                                          \
    label_name:                                                             \
    _TBS_STMT_EMPTY;                                                        \
)

// threading

#define _TBS_EXPRESSION_WITH_ACCESS_COUNT(n, enabled, expression, enter_code, exit_code, if_disabled_init_code) \
({                                                          \
    static pthread_mutex_t _TBS_SYM_NAME(n, section_lock) = PTHREAD_MUTEX_INITIALIZER;\
    static unsigned int _TBS_SYM_NAME(n, access_count) = 0;                 \
    if (enabled) {                                                          \
        pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));                \
        if (_TBS_SYM_NAME(n, access_count)++ == 0) {                        \
            enter_code                                                      \
        }                                                                   \
        pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));                \
    } else {                                                                \
        static bool _TBS_SYM_NAME(n, initialized) = false;                  \
        if (!_TBS_SYM_NAME(n, initialized)) {                               \
            pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));            \
            if (!_TBS_SYM_NAME(n, initialized)) {                           \
                _TBS_SYM_NAME(n, initialized) = true;                       \
                if_disabled_init_code;                                      \
            }                                                               \
            pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));            \
        }                                                                   \
    }                                                                       \
    const typeof(expression) _TBS_SYM_NAME(n, res) = (expression);                \
    if (enabled) {                                                          \
        pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));                \
        if (--_TBS_SYM_NAME(n, access_count) == 0) {                        \
            exit_code                                                       \
        }                                                                   \
        pthread_mutex_lock(&_TBS_SYM_NAME(n, section_lock));                \
    }                                                                       \
    _TBS_SYM_NAME(n, res);                                                  \
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

#define _TBS_ENC(n, code, ...)                                              \
_TBS_STMT_WRAPPER(                                                          \
    goto _TBS_SYM_NAME(n, section_start); \
    goto _TBS_SYM_NAME(n, section_end); \
    const _tbs_section_config _TBS_SYM_NAME(n, config) =                    \
        _TBS_SECTION_CONFIG_DEFAULT(__VA_ARGS__);                           \
    _TBS_EXPRESSION_WITH_ACCESS_COUNT(                                         \
        n,                                                                  \
        _TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), thread_safe) &&   \
        _TBS_SECTION_CONFIG_GET(_TBS_SYM_NAME(n, config), re_encrypt),      \
        ({                                                  \
            _TBS_LABEL(_TBS_SYM_NAME(n, section_start));                    \
            code;                                                           \
            _TBS_LABEL(_TBS_SYM_NAME(n, section_end));                      \
            0;\
        }),                                                                  \
        _TBS_STMT_WRAPPER(                                                  \
            /* decrypt */                                                   \
        ),                                                                  \
        _TBS_STMT_WRAPPER(                                                  \
            /* encrypt */                                                   \
        ),                                                                  \
        _TBS_STMT_WRAPPER(                                                  \
            /* descrypt */                                                  \
        )                                                                   \
    )                                                                       \
)

#define tbs_enc(code, ...)                                                  \
_TBS_ENC(__COUNTER__, _TBS_STMT_WRAPPER(code), __VA_ARGS__)


int main() {
    const tbs_config cfg = tbs_config_default(thread_safe: false);

    _TBS_USE_VAR(cfg);

    tbs_enc({
        printf("hey\n");
    });

    // tbs_enc({
    //     printf("ho\n");
    //     tbs_enc({
    //         printf("go\n");
    //     });
    // });
}