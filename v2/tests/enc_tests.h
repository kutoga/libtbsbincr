#ifndef __TBS_ENC_TESTS_H__
#define __TBS_ENC_TESTS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <tbs/enc.h>

/*
 * All "enc" tests are in this header file as inline functions defined.
 * They are used in C and C++ code ensure the code works with both
 * languages.
 */


static inline tbs_restricted_opt bool test_tbs_enc_exp_single_expression() {
    const int a = 1;
    int b = 2;

    const int res = tbs_enc_exp(a + b);

    return res == 3;
}


static inline tbs_restricted_opt bool test_tbs_enc_exp_multiple_expressions() {
    const int a = 1;
    const int b = 2;

    const int res1 = tbs_enc_exp(a + b);
    const int res2 = tbs_enc_exp(a * b);
    const int res3 = tbs_enc_exp(a - b);

    return res1 ==  3 && \
           res2 ==  2 && \
           res3 == -1;
}


static inline tbs_restricted_opt bool test_tbs_enc_exp_nested_expressions() {
    const int a = 1;
    const int b = 2;

    const int res = tbs_enc_exp(tbs_enc_exp(a * b) + tbs_enc_exp(a - b)); 

    return res == 1;
}


static inline tbs_restricted_opt bool test_tbs_enc_exp_single_statement() {
    const int a = 1;
    int b = 2;

    int res;
    tbs_enc({
        res = a + b;
    });

    return res == 3;
}


static inline tbs_restricted_opt bool test_tbs_enc_exp_multiple_statements() {
    const int a = 1;
    const int b = 2;

    int res1, res2, res3;
    tbs_enc(res1 = a + b);
    tbs_enc(res2 = a * b);
    tbs_enc(res3 = a - b);

    return res1 ==  3 && \
           res2 ==  2 && \
           res3 == -1;
}


static inline tbs_restricted_opt bool test_tbs_enc_exp_nested_statements() {
    const int a = 1;
    const int b = 2;

    int res;
    tbs_enc({
        int res_tmp1;
        int res_tmp2;
        tbs_enc(res_tmp1 = a * b);
        tbs_enc(res_tmp2 = a - b);
        res = res_tmp1 + res_tmp2;
    });

    return res == 1;
}


static inline tbs_restricted_opt bool test_tbs_enc_exp_mixed_statements() {
    const int a = 1;
    const int b = 2;

    int res;
    tbs_enc({
        int res_tmp1 = tbs_enc_exp(a * b);
        int res_tmp2 = tbs_enc_exp(a - b);
        res = tbs_enc_exp(({
            int tmp;
            tbs_enc(tmp = res_tmp1 + res_tmp2);
            tmp;
        }));
    });

    return res == 1;
}


#ifdef __cplusplus
}
#endif

#endif
