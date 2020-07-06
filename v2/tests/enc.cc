#include <gtest/gtest.h>
#include "enc_tests_c.h"
#include "enc_tests.h"

TEST(tbs_enc_exp, c_single_expression) {
    ASSERT_TRUE(test_tbs_enc_exp_single_expression());
}

TEST(tbs_enc_exp, cpp_single_expression) {
    ASSERT_TRUE(test_c_tbs_enc_exp_single_expression());
}

// TEST(tbs_enc_exp, single_expression) {
//     const int a = 1;
//     int b = 2;

//     const int res = tbs_enc_exp(a + b);

//     ASSERT_EQ(res, 3);
// }


// TEST(tbs_enc_exp, multiple_expressions) {
//     const int a = 1;
//     const int b = 2;

//     const int res1 = tbs_enc_exp(a + b);
//     const int res2 = tbs_enc_exp(a * b);
//     const int res3 = tbs_enc_exp(a - b);

//     ASSERT_EQ(res1, 3);
//     ASSERT_EQ(res2, 2);
//     ASSERT_EQ(res3, -1);
// }


// TEST(tbs_enc_exp, nested_expressions) {
//     const int a = 1;
//     const int b = 2;

//     const int res = tbs_enc_exp(tbs_enc_exp(a * b) + tbs_enc_exp(a - b));

//     ASSERT_EQ(res, 1);
// }


// TEST(tbs_enc_exp, single_statement) {
//     const int a = 1;
//     int b = 2;

//     int res;
//     tbs_enc({
//         res = a + b;
//     });

//     ASSERT_EQ(res, 3);
// }


// TEST(tbs_enc_exp, multiple_statements) {
//     const int a = 1;
//     const int b = 2;

//     int res1, res2, res3;
//     tbs_enc(res1 = a + b);
//     tbs_enc(res2 = a * b);
//     tbs_enc(res3 = a - b);

//     ASSERT_EQ(res1, 3);
//     ASSERT_EQ(res2, 2);
//     ASSERT_EQ(res3, -1);
// }


// TEST(tbs_enc_exp, nested_statements) {
//     const int a = 1;
//     const int b = 2;

//     int res;
//     tbs_enc({
//         int res_tmp1;
//         int res_tmp2;
//         tbs_enc(res_tmp1 = a * b);
//         tbs_enc(res_tmp2 = a - b);
//         res = res_tmp1 + res_tmp2;
//     });

//     ASSERT_EQ(res, 1);
// }
