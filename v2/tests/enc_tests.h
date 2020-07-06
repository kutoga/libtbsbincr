#ifndef __TBS_ENC_TESTS_H__
#define __TBS_ENC_TESTS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <tbs/enc.h>

static inline bool test_tbs_enc_exp_single_expression() {
    const int a = 1;
    int b = 2;

    const int res = tbs_enc_exp(a + b);

    return res == 3;
}

#ifdef __cplusplus
}
#endif

#endif
