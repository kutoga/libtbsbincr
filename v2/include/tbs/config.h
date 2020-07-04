#ifndef __TBS_CONFIG_H__
#define __TBS_CONFIG_H__

#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
#include "random.h"
#include "crypto_algorithm.h"

/*
 * struct attributes for tbs_config
 */
#define _TBS_CONFIG_ENTRIES(constness_modifier)                             \
    constness_modifier bool thread_safe;                                    \
    constness_modifier bool re_encrypt;                                     \
    constness_modifier bool re_enetrant;                                    \
    tbs_random *constness_modifier keygen;                                  \
    tbs_crypto_algorithm_initializer constness_modifier crypto_algorithm_init;

/*
 * Default values for tbs_config
 */
#define _TBS_CONFIG_DEFAULTS                                                \
    thread_safe:      true,                                                 \
    re_encrypt:       true,                                                 \
    re_enetrant:      true,                                                 \
    keygen:           &tbs_random_time_based,                               \
    crypto_algorithm_init: tbs_crypto_algorithm_simple_init,

typedef struct tbs_config {
    _TBS_CONFIG_ENTRIES()
} tbs_config;

/*
 * Default initialize a tbs_config and allow it to override some
 * fields. E.g.
 * tbs_config_default(thread_safe: false, re_encrypt: false)
 * will use default values, except for thread_safe and re_encrypt.
 */
#define tbs_config_default(...)                                             \
_TBS_STRUCT_IGNORE_OVERRIDE_EXP(((tbs_config) {                             \
    _TBS_CONFIG_DEFAULTS                                                    \
    __VA_ARGS__                                                             \
}))

typedef struct _tbs_section_config {
    _TBS_CONFIG_ENTRIES(const)
    const tbs_config *const settings;
} _tbs_section_config;

#define _TBS_SECTION_CONFIG_DEFAULTS                                        \
    _TBS_CONFIG_DEFAULTS                                                    \
    settings: NULL,

#define _TBS_SECTION_CONFIG_DEFAULT(...)                                    \
_TBS_STRUCT_IGNORE_OVERRIDE_EXP(((_tbs_section_config) {                    \
    _TBS_SECTION_CONFIG_DEFAULTS                                            \
    __VA_ARGS__                                                             \
}))

#define _TBS_SECTION_CONFIG_GET(config, key)                                (config.settings ? config.settings->key : config.key)

#endif
