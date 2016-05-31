#ifndef __TBS_LOG_CORE_H__
#define __TBS_LOG_CORE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <tbs/util.h>

#ifndef TBS_LOG_DISABLE
#include <stdio.h>
#include <time.h>

void tbs_log_buffer_hex_dump(unsigned char *buffer, unsigned char *output, size_t buffer_len);

#ifdef WIN32
/* Include winsock2, because it MUST be included before windows.h (ugly) */
#include <winsock2.h>
#include <windows.h>
#include <process.h>

#define TBS_LOG_GET_THREAD_ID                                   ((unsigned long)GetCurrentThreadId())
#else
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#define TBS_LOG_GET_THREAD_ID                                   ((unsigned long)(pid_t)syscall(SYS_gettid))
#endif

void tbs_log_init(void);
void tbs_log_cleanup(void);
int tbs_log_is_enabled(void);
void tbs_log_enable(int enable);

#ifndef TBS_LOG_DISABLE_THREAD_LOCK

void __tbs_log_output_lock__(void);
void __tbs_log_output_unlock__(void);
#else

static inline void __attribute__((always_inline)) __tbs_log_output_lock__(void) {
}

static inline void __attribute__((always_inline)) __tbs_log_output_unlock__(void) {
}
#endif

time_t __tbs_log_get_init_time__(void);
int __tbs_log_nonlock_is_enabled__(void);

#define __tbs_log_printd__(file, level, ...)                    \
TBS_UTIL_STATEMENT_WRAPPER(                                     \
    __tbs_log_output_lock__();                                  \
    if (__tbs_log_nonlock_is_enabled__()) {                     \
        fprintf((file), "[%06d] [%07ld] [%30s:%-4d] [%25s] ",   \
            (int)(time(0) - __tbs_log_get_init_time__()),       \
            TBS_LOG_GET_THREAD_ID, __FILE__, __LINE__,          \
            __FUNCTION__);                                      \
        fprintf((file), level ": " __VA_ARGS__);                \
        fputc('\n', (file));                                    \
        fflush(file);                                           \
    }                                                           \
    __tbs_log_output_unlock__();                                \
)

#else
#define __tbs_log_printd__(file, level, ...)                    TBS_UTIL_STATEMENT_EMPTY()
#endif

#define tbs_log_trace(...)                                      __tbs_log_printd__(stdout, "TRACE", __VA_ARGS__)
#define tbs_log_info(...)                                       __tbs_log_printd__(stdout, "INFO ", __VA_ARGS__)
#define tbs_log_warn(...)                                       __tbs_log_printd__(stderr, "WARN ", __VA_ARGS__)
#define tbs_log_err(...)                                        __tbs_log_printd__(stderr, "ERROR", __VA_ARGS__)
#define tbs_log_fatal(...)                                      __tbs_log_printd__(stderr, "FATAL", __VA_ARGS__)

#ifdef TBS_LOG_DISABLE
static inline void __attribute__((always_inline)) tbs_log_init(void) {
}

static inline void __attribute__((always_inline)) tbs_log_cleanup(void) {
}

static inline int __attribute__((always_inline)) tbs_log_is_enabled(void) {
    return 0;
}

static inline void __attribute__((always_inline)) tbs_log_enable(int enable) {
    TBS_UTIL_USE_VAR(enable);
}

static inline void __attribute__((always_inline)) tbs_log_buffer_hex_dump(unsigned char *buffer, unsigned char *output, size_t buffer_len) {
    TBS_UTIL_USE_VAR(buffer);
    TBS_UTIL_USE_VAR(output);
    TBS_UTIL_USE_VAR(buffer_len);
}
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <typeinfo>

/* TODO: Create a macro which allows silent exceptions or not silent exceptions. */

/*
namespace tbs {
    namespace log {
        template<typename T>
        static inline void __attribute__((always_inline)) __throw_ex__(const char *file, int line, const std::string& message) {
#ifdef TBS_LOG_DISABLE
            TBS_UTIL_USE_VAR(file);
            TBS_UTIL_USE_VAR(line);
            throw T(message);
#else
            tbs_log_err("Exception at %s:%d [%s]: %s", file, line, typeid(T).name(), message.c_str());
            throw T("");
#endif
        }

        template<typename T, typename... ARGS>
        static inline void __attribute__((always_inline)) __throw_ex__(const char *file, int line, const std::string& message, const ARGS&... args) {
#ifdef TBS_LOG_DISABLE
            TBS_UTIL_USE_VAR(file);
            TBS_UTIL_USE_VAR(line);
            throw T(message, args...);
#else
            TBS_UTIL_USE_VARGS(args);
            tbs_log_err("Exception at %s:%d (additional arguments ignored) [%s]: %s", file, line, typeid(T).name(), message.c_str());
            throw T("", args...);
#endif
        }

        template<typename T, typename... ARGS>
        static inline void __attribute__((always_inline)) __throw_ex__(const char *file, int line, const ARGS&... args) {
#ifdef TBS_LOG_DISABLE
            TBS_UTIL_USE_VAR(file);
            TBS_UTIL_USE_VAR(line);
            throw T(args...);
#else
            TBS_UTIL_USE_VARGS(args);
            tbs_log_err("Exception at %s (additional arguments ignored) [%s] thrown. No message available.", file, line, typeid(T).name());
            throw T(args...);
#endif
        }
    }
}*/

#ifdef TBS_LOG_DISABLE
#define tbs_log_throw(TYPE, MESSAGE)                            \
TBS_UTIL_STATEMENT_WRAPPER(                                     \
    TBS_UTIL_USE_VAR(MESSAGE);                                  \
    throw TYPE("");                                             \
)
#define tbs_log_throw_args(TYPE, MESSAGE, ...)                  \
TBS_UTIL_STATEMENT_WRAPPER(                                     \
    TBS_UTIL_USE_VAR(MESSAGE);                                  \
    throw TYPE("", __VA_ARGS__);                                \
)
#else
#define tbs_log_throw(TYPE, MESSAGE)                            \
TBS_UTIL_STATEMENT_WRAPPER(                                     \
    tbs_log_err("Exception [%s]: %s", typeid(TYPE).name(),      \
        std::string(MESSAGE).c_str());                          \
    throw TYPE(MESSAGE);                                        \
)
#define tbs_log_throw_args(TYPE, MESSAGE, ...)                  \
TBS_UTIL_STATEMENT_WRAPPER(                                     \
    tbs_log_err("Exception [%s]: %s", typeid(TYPE).name(),      \
        std::string(MESSAGE).c_str());                          \
    throw TYPE(MESSAGE, __VA_ARGS__);                           \
)
#endif

#endif

#endif /* __TBS_LOG_CORE_H__ */
