#ifndef __TBS_LOG_H__
#define __TBS_LOG_H__

#include "common.h"

#define _TBS_LOG_PRINTD(file, level, ...)                                   \
_TBS_STMT_WRAPPER(                                                          \
    fprintf((file), "[%30s:%-4d] [%25s] ", __FILE__, __LINE__, __FUNCTION__);\
    fprintf((file), level ": " __VA_ARGS__);                                \
    fputc('\n', (file));                                                    \
    fflush(file);                                                           \
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

#endif
