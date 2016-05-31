#include <stdio.h>
#include <math.h>
#include <tbs/bincr/core.h>
#include <tbs/log/core.h>

/*
 * It is highly recommended to disable optimizations for all functions
 * which use the encryption. To do this, the macro TBS_UTIL_DISABLE_OPTIMIZATIONS
 * may be used. If this is not used the code has to be tested well, because
 * optimization levels over -O1 make g++ do weired things and the code
 * often does no longer work correctly.
 */
//#undef TBS_UTIL_DISABLE_OPTIMIZATIONS

void test01(void);
void test02(void);
void test03(void);
void test04(void);
void test05(void);
void test06(void);
void test07(void);
void test08(void);
void test09(void);
void test10(void);
void test11(void);

int main(void) {
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
    test07();
    test08();
    test09();
    test10();
    test11();
    return 0;
}

/* Test an inline encrypted code. Descrypt once. */
void TBS_UTIL_DISABLE_OPTIMIZATIONS test01(void) {
    int a = 0;
    tbs_enc_code(
        a += (int)sin(0.5) + 1;
    );
    if (a == 1) {
        printf("test01 ok\n");
    }
}

/* Test multiple encrypted codes. Descrypt once. */
void TBS_UTIL_DISABLE_OPTIMIZATIONS test02(void) {
    int a = 0;
    tbs_enc_code_n(0,
        a += (int)sin(0.5) + 1;
    );
    tbs_enc_code_n(1,
        a += (int)cos(0.5) + 1;
    );
    tbs_enc_code_n(2,
        tbs_enc_code_n(3,
            tbs_enc_code_n(4,
                a += (int)exp(0.5);
            );
        );
    );
    if (a == 3) {
        printf("test02 ok\n");
    }
}

/* Test an encrypted procedure */
void TBS_UTIL_DISABLE_OPTIMIZATIONS test03(void) tbs_enc_proc(
    int a = 0;
    a += (int)sin(0.5) + 1;
    if (a == 1) {
        printf("test03 ok\n");
    }
)

/* Test an encrypted statement. */
void TBS_UTIL_DISABLE_OPTIMIZATIONS test04(void) {
    int a = 0;
    a += tbs_enc_stmt((int)sin(0.5) + 1);
    if (a == 1) {
        printf("test04 ok\n");
    }
}

/* Test multiple encrypted statements. */
void TBS_UTIL_DISABLE_OPTIMIZATIONS test05(void) {
    int a = 0;
    a += tbs_enc_stmt_n(0, (int)cos(0.5) + 1);
    a += tbs_enc_stmt_n(1, (int)sin(0.5) + 1);
    a += tbs_enc_stmt_n(2, (int)cos(0.5) + 1);
    if (tbs_enc_stmt_n(3, a == 3)) {
        printf("test05 ok\n");
    }
}

/* Test a combination of the things from before. */
void TBS_UTIL_DISABLE_OPTIMIZATIONS test06(void) tbs_enc_proc(

    // TODO: Fix this test
    int a = 0;
    tbs_enc_code_n(0,
        //tbs_enc_code_n(1,
            a += tbs_enc_stmt_n(3, (int)cos(0.5)) + 1;// + tbs_enc_stmt_n(4, 1);
        //);
    );
    tbs_enc_stmt_n(5, a *= 2);
    if (a == 2) {
        printf("test06 ok\n");
    }
)

/* Do manual encrpytion and decryption. */
void TBS_UTIL_DISABLE_OPTIMIZATIONS test07(void) {
    int a = 0;
    tbs_enc_decrypt();
    tbs_enc_code(
        a += (int)sin(0.5) + 1;
    );
    tbs_enc_encrypt(0x1234);
    if (a == 1) {
        printf("test07 ok\n");
    }
}

/* Use now the thread safe decryption. */
void TBS_UTIL_DISABLE_OPTIMIZATIONS test08(void) {
    tbs_enc_threaded_n(0);
    tbs_enc_threaded_n(1);

    int a = 0;
    
    // TODO: Test auto decryption
    
    /* Manual decryption required. (Store no key! => 0) */
    tbs_enc_decrypt_nt(0, 0);
    tbs_enc_code_nt(0,
        a += (int)sin(0.5) + 1;
    );
    
    /* Manual decryption required. (Store no key! => 0) */
    tbs_enc_decrypt_nt(1, 0);
    tbs_enc_code_nt(1,
        a += (int)cos(0.5) + 1;
    );
    if (a == 2) {
        printf("test08 ok\n");
    }
}

/* Use now full thread safe encryption and decryption. */
unsigned TBS_UTIL_DISABLE_OPTIMIZATIONS fac_test(unsigned n) {
    unsigned res = 1;
    tbs_enc_code_ft(
        if (n >= 2) {
            res = n * fac_test(n -1);
        }
    );
    return res;
}
void TBS_UTIL_DISABLE_OPTIMIZATIONS test09(void) {
    int a = 0;
    a += fac_test(3);
    a += fac_test(3);
    if (a == 2 * 1 * 2 * 3) {
        printf("test09 ok\n");
    }
}

/* Test a thread safe procedure (including auto re-encrpytion. */
static int test10_a;
void TBS_UTIL_DISABLE_OPTIMIZATIONS rec_test(unsigned n) tbs_enc_proc_t(
    test10_a += 1;
    if (n > 0) {
        rec_test(n - 1);
    }
)
void TBS_UTIL_DISABLE_OPTIMIZATIONS test10(void) {
    test10_a = 0;
    rec_test(10);
    if (test10_a == 11) {
        printf("test10 ok\n");
    }
}

/* Do a thread safe test with multiple encrypted regions. */
unsigned TBS_UTIL_DISABLE_OPTIMIZATIONS fac_test2(unsigned n) {
    unsigned res = 1;
    tbs_enc_code_ft_n(0,
        if (n >= 2) {
            //tbs_enc_code_ft_n(1,
                res = n * fac_test(n -1);
            //);
        }
    );
    return res;
}
void TBS_UTIL_DISABLE_OPTIMIZATIONS test11(void) {
    int a = 0;
    a += fac_test2(3);
    a += fac_test2(3);
    if (a == 2 * 1 * 2 * 3) {
        printf("test11 ok\n");
    }
}

/* TODO: Test some more macros, but these are only */ 



