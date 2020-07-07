#ifndef __TBS_ENC_TESTS_C_H__
#define __TBS_ENC_TESTS_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool test_c_tbs_enc_exp_single_expression();

bool test_c_tbs_enc_exp_multiple_expressions();

bool test_c_tbs_enc_exp_nested_expressions();

bool test_c_tbs_enc_exp_single_statement();

bool test_c_tbs_enc_exp_multiple_statements();

bool test_c_tbs_enc_exp_nested_statements();

bool test_c_tbs_enc_exp_mixed_statements();

bool test_c_tbs_enc_exp_return_in_statement();

#ifdef __cplusplus
}
#endif

#endif
