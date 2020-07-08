#ifndef __TBS_LOG_H__
#define __TBS_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "common.h"

#define _TBS_LOG_PRINTD(file, level, ...)                                       \
_TBS_STMT_WRAPPER(                                                              \
    FILE *_tbs_fh = (file);                                                     \
    flockfile(_tbs_fh);                                                         \
    fprintf(_tbs_fh, "[%30s:%-4d] [%25s] ", __FILE__, __LINE__, __FUNCTION__);  \
    fprintf(_tbs_fh, level ": " __VA_ARGS__);                                   \
    fputc('\n', _tbs_fh);                                                       \
    fflush(_tbs_fh);                                                            \
    funlockfile(_tbs_fh);                                                       \
)

#ifdef TBS_LOG_ENABLE
#define _tbs_log_trace(...)                                                 _TBS_LOG_PRINTD(stdout, "TRACE", __VA_ARGS__)
#define _tbs_log_info(...)                                                  _TBS_LOG_PRINTD(stdout, "INFO ", __VA_ARGS__)
#define _tbs_log_warn(...)                                                  _TBS_LOG_PRINTD(stderr, "WARN ", __VA_ARGS__)
#define _tbs_log_err(...)                                                   _TBS_LOG_PRINTD(stderr, "ERROR", __VA_ARGS__)
#define _tbs_log_fatal(...)                                                 _TBS_LOG_PRINTD(stderr, "FATAL", __VA_ARGS__)
#else
#define _tbs_log_trace(...)                                                 _TBS_STMT_EMPTY
#define _tbs_log_info(...)                                                  _TBS_STMT_EMPTY
#define _tbs_log_warn(...)                                                  _TBS_STMT_EMPTY
#define _tbs_log_err(...)                                                   _TBS_STMT_EMPTY
#define _tbs_log_fatal(...)                                                 _TBS_STMT_EMPTY
#endif

#ifdef __cplusplus
}
#endif

#endif
