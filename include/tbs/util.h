#ifndef __TBS_UTIL_H__
#define __TBS_UTIL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define TBS_UTIL_STATEMENT_WRAPPER(code)                        do { code } while(0)
#define TBS_UTIL_STATEMENT_EMPTY()                              do { } while (0)

#define TBS_UTIL_USE_VAR(v)                                     ((void)(v))

#ifdef __clang__
#define TBS_UTIL_DISABLE_OPTIMIZATIONS                          __attribute__((optnone))
#else
#define TBS_UTIL_DISABLE_OPTIMIZATIONS                          __attribute__((optimize("O0")))
#endif

#ifdef WIN32
/* Include winsock2, because it MUST be included before windows.h (ugly) */
#include <winsock2.h>
#include <windows.h>
#include <process.h>

#define TBS_UTIL_MUTEX_T                                        CRITICAL_SECTION
#define TBS_UTIL_MUTEX_INIT(mp)                                 InitializeCriticalSection(mp)
#define TBS_UTIL_MUTEX_DESTROY(mp)                              DeleteCriticalSection(mp)
#define TBS_UTIL_MUTEX_LOCK(mp)                                 EnterCriticalSection(mp)
#define TBS_UTIL_MUTEX_UNLOCK(mp)                               LeaveCriticalSection(mp)

#else
#include <pthread.h>
#include <sys/syscall.h>

#define TBS_UTIL_MUTEX_T                                        pthread_mutex_t
#define TBS_UTIL_MUTEX_INIT(mp)                                 ((*(mp)) = (TBS_UTIL_MUTEX_T)PTHREAD_MUTEX_INITIALIZER)
#define TBS_UTIL_MUTEX_DESTROY(mp)                              TBS_UTIL_STATEMENT_EMPTY()
#define TBS_UTIL_MUTEX_LOCK(mp)                                 pthread_mutex_lock(mp)
#define TBS_UTIL_MUTEX_UNLOCK(mp)                               pthread_mutex_unlock(mp)
#endif

#define TBS_UTIL_COUNTER                                        __COUNTER__

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#define TBS_UTIL_USE_VARGS(args)                                TBS_UTIL_USE_VAR(sizeof...(args));
#endif

#endif /* __TBS_UTIL_H__ */
