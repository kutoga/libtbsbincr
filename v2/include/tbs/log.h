#ifndef __TBS_LOG_H__
#define __TBS_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "platform.h"
#include "common.h"

#ifdef _TBS_IS_LINUX
#define _TBS_LOCK_FILE(fh)                                                      flockfile(fh)
#define _TBS_UNLOCK_FILE(fh)                                                    funlockfile(fh)
#else
#define _TBS_LOCK_FILE                                                          _lock_file
#define _TBS_UNLOCK_FILE                                                        _unlock_file
#endif

#define _TBS_LOG_PRINTD(file, level, ...)                                       \
_TBS_STMT_WRAPPER(                                                              \
    FILE *_tbs_fh = (file);                                                     \
    _TBS_LOCK_FILE(_tbs_fh);                                                    \
    fprintf(_tbs_fh, "[%30s:%-4d] [%25s] ", __FILE__, __LINE__, __FUNCTION__);  \
    fprintf(_tbs_fh, level ": " __VA_ARGS__);                                   \
    fputc('\n', _tbs_fh);                                                       \
    _TBS_UNLOCK_FILE(_tbs_fh);                                                  \
    fflush(_tbs_fh);                                                            \
)

#ifdef TBS_LOG_ENABLE
#include <stdlib.h>
#include <string.h>

#define _tbs_log_trace(...)                                                     _TBS_LOG_PRINTD(stdout, "TRACE", __VA_ARGS__)
#define _tbs_log_info(...)                                                      _TBS_LOG_PRINTD(stdout, "INFO ", __VA_ARGS__)
#define _tbs_log_warn(...)                                                      _TBS_LOG_PRINTD(stderr, "WARN ", __VA_ARGS__)
#define _tbs_log_error(...)                                                     _TBS_LOG_PRINTD(stderr, "ERROR", __VA_ARGS__)
#define _tbs_log_fatal(...)                                                     _TBS_LOG_PRINTD(stderr, "FATAL", __VA_ARGS__)

#define _tbs_log_stringify_memory(memory_start, memory_length, var_name, code)  \
_TBS_STMT_WRAPPER({                                                             \
    const size_t _tbs_size_per_char = strlen("0xFF ");                          \
    char *var_name = malloc((memory_length) * _tbs_size_per_char + 1);                           \
    for (int i = 0; i < (int)(memory_length); ++i) {                                   \
        sprintf(&var_name[_tbs_size_per_char * i], "0x%02X ", (unsigned char)(memory_start)[i]);               \
    }                                                                           \
    code;                                                                       \
    free(var_name);                                                             \
})

#else
#define _tbs_log_trace(...)                                                     _TBS_STMT_EMPTY
#define _tbs_log_info(...)                                                      _TBS_STMT_EMPTY
#define _tbs_log_warn(...)                                                      _TBS_STMT_EMPTY
#define _tbs_log_error(...)                                                     _TBS_STMT_EMPTY
#define _tbs_log_fatal(...)                                                     _TBS_STMT_EMPTY

#define _tbs_log_stringify_memory(memory_start, memory_length, var_name, code)  _TBS_STMT_EMPTY
#endif


#ifdef __cplusplus
}
#endif

#endif
