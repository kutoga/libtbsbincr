#include <gtest/gtest.h>
#include <tbs/enc.h>


TEST(tbs_enc_exp, single_expression) {
    const int a = 1;
    int b = 2;

    const int res = tbs_enc_exp(a + b);

    ASSERT_EQ(res, 3);
}


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

//     ASSERT_EQ(res, -2);
// }