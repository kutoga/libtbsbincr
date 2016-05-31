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

unsigned int TBS_UTIL_DISABLE_OPTIMIZATIONS fac(unsigned int n) {
    unsigned int res = 0;
    
    /* Encrypt with full threaded support (auto reencrypt after done) */
    tbs_enc_code_ft(
        if (n < 2) {
            res = 1;
        } else {
            res = n * fac(n - 1);
        }
    );
    
    return res;
}

/* TODO: Give an example for a threaded procedure. */
/* TODO: Give an example for a threaded fuction (manual inc and dec) */

int TBS_UTIL_DISABLE_OPTIMIZATIONS main(void) {
    tbs_log_init();
    
    /* A very very basic test. */
    int a = 1;
    
    uint16_t key = tbs_enc_gen_key();
    
    tbs_enc_threaded_n(N);
    
    tbs_enc_code(
        a--;
        printf("%d\n", a);
    );
    
    {
        tbs_enc_encrypt(key);
        key = tbs_enc_gen_key();
        tbs_enc_decrypt();
    }
    {
        tbs_enc_encrypt(key);
        key = tbs_enc_gen_key();
        tbs_enc_decrypt();
    }
    
    printf("Recursive call.\n");
    printf("4! = %u\n", fac(4));
    
    tbs_log_cleanup();
    return a;
}

