#include <stdio.h>
#include <tbs/bincr/core.h>
#include <tbs/log/core.h>

/*
 * It is highly recommended to disable optimizations for all functions
 * which use the encryption. To do this, the macro TBS_UTIL_DISABLE_OPTIMIZATIONS
 * may be used. If this is not used the code has to be tested well, because
 * optimization levels over -O1 make g++ do weird things and the code
 * often does no longer work correctly.
 */
//#undef TBS_UTIL_DISABLE_OPTIMIZATIONS

unsigned TBS_UTIL_DISABLE_OPTIMIZATIONS fac_test(unsigned n) {
    unsigned res = 1;
    tbs_enc_code_ft(
        if (n >= 2) {
            res = n * fac_test(n -1);
        }
    );
    return res;
}

int main(void) {
    tbs_log_init();
    unsigned n = 4;
    printf("fac(%u) = %u\n", n, fac_test(n));
    tbs_log_cleanup();
    return 0;
}

