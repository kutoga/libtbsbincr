#include <time.h>
#include <tbs/log/core.h>

#ifdef WIN32
#include <windows.h>

#define sleep(s)                Sleep(1000 * (s))
#else

#include <unistd.h>
#endif

int main(void) {
    tbs_log_init();
    
    int a = 10;
    int b = 5;
    (void)a;
    (void)b;
    
    tbs_log_trace("Calculate: %d + %d = %d", a, b, a + b);
    sleep(1);
    tbs_log_info("Calculate: %d + %d = %d", a, b, a + b);
    sleep(1);
    tbs_log_warn("Calculate: %d + %d = %d", a, b, a + b);
    sleep(1);
    tbs_log_err("Calculate: %d + %d = %d", a, b, a + b);
    sleep(1);
    tbs_log_fatal("Calculate: %d + %d = %d", a, b, a + b);
    
    tbs_log_cleanup();
    return 0;
}
