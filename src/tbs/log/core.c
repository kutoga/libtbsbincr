#include <tbs/log/core.h>

#ifndef TBS_LOG_DISABLE

#ifndef TBS_LOG_DISABLE_THREAD_LOCK

static int tbs_log_lock_initialized = 0;
static TBS_UTIL_MUTEX_T tbs_log_lock;

static TBS_UTIL_MUTEX_T *tbs_log_get_mutex(void) {
    if (!tbs_log_lock_initialized) {
        TBS_UTIL_MUTEX_INIT(&tbs_log_lock);
        tbs_log_lock_initialized = 1;
    }
    return &tbs_log_lock;
}

void __tbs_log_output_lock__(void) {
    TBS_UTIL_MUTEX_LOCK(tbs_log_get_mutex());
}

void __tbs_log_output_unlock__(void) {
    TBS_UTIL_MUTEX_UNLOCK(tbs_log_get_mutex());
}

#endif

static time_t tbs_log_init_time = 0;
static int tbs_log_enabled = 1;

time_t __tbs_log_get_init_time__(void) {
    return tbs_log_init_time;
}

int __tbs_log_nonlock_is_enabled__(void) {
    return tbs_log_enabled;
}

void tbs_log_init(void) {
#ifndef TBS_LOG_DISABLE_THREAD_LOCK
    tbs_log_get_mutex();
#endif
    tbs_log_init_time = time(0);
}

void tbs_log_cleanup(void) {
#ifndef TBS_LOG_DISABLE_THREAD_LOCK
    if (tbs_log_lock_initialized) {
        TBS_UTIL_MUTEX_DESTROY(&tbs_log_lock);
        tbs_log_lock_initialized = 0;
    }
#endif
}

int tbs_log_is_enabled(void) {
    int result;
#ifndef TBS_LOG_DISABLE_THREAD_LOCK
    __tbs_log_output_lock__();
#endif
    result = __tbs_log_nonlock_is_enabled__();
#ifndef TBS_LOG_DISABLE_THREAD_LOCK
    __tbs_log_output_unlock__();
#endif
    return result;
}

void tbs_log_enable(int enable) {
#ifndef TBS_LOG_DISABLE_THREAD_LOCK
    __tbs_log_output_lock__();
#endif
    tbs_log_enabled = enable;
#ifndef TBS_LOG_DISABLE_THREAD_LOCK
    __tbs_log_output_unlock__();
#endif
}

void tbs_log_buffer_hex_dump(unsigned char *buffer, unsigned char *output, size_t buffer_len) {
    size_t i = 0;
    for (i = 0; i < buffer_len; i++) {
        snprintf((char *)&output[3 * i], 3, "%02X", (unsigned)buffer[i] & 0xFF);
        if (i == (buffer_len - 1)) {
            output[3 * i + 2] = '\0';
        } else {
            output[3 * i + 2] = ' ';
        }
    }
}

#endif

