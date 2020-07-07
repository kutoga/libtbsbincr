#include <gtest/gtest.h>
#include "enc_tests_c.h"
#include "enc_tests.h"

TEST(tbs_enc_exp, c_single_expression) {
    ASSERT_TRUE(test_c_tbs_enc_exp_single_expression());
}

TEST(tbs_enc_exp, cpp_single_expression) {
    ASSERT_TRUE(test_tbs_enc_exp_single_expression());
}

TEST(tbs_enc_exp, c_multiple_expressions) {
    ASSERT_TRUE(test_c_tbs_enc_exp_multiple_expressions());
}

TEST(tbs_enc_exp, cpp_multiple_expressions) {
    ASSERT_TRUE(test_tbs_enc_exp_multiple_expressions());
}

TEST(tbs_enc_exp, c_nested_expressions) {
    ASSERT_TRUE(test_c_tbs_enc_exp_nested_expressions());
}

TEST(tbs_enc_exp, cpp_nested_expressions) {
    ASSERT_TRUE(test_tbs_enc_exp_nested_expressions());
}

TEST(tbs_enc_exp, c_single_statement) {
    ASSERT_TRUE(test_c_tbs_enc_exp_single_statement());
}

TEST(tbs_enc_exp, cpp_single_statement) {
    ASSERT_TRUE(test_tbs_enc_exp_single_statement());
}

TEST(tbs_enc_exp, c_multiple_statements) {
    ASSERT_TRUE(test_c_tbs_enc_exp_multiple_statements());
}

TEST(tbs_enc_exp, cpp_multiple_statements) {
    ASSERT_TRUE(test_tbs_enc_exp_multiple_statements());
}

TEST(tbs_enc_exp, c_nested_statements) {
    ASSERT_TRUE(test_c_tbs_enc_exp_nested_statements());
}

TEST(tbs_enc_exp, cpp_nested_statements) {
    ASSERT_TRUE(test_tbs_enc_exp_nested_statements());
}

TEST(tbs_enc_exp, c_mixed_statements) {
    ASSERT_TRUE(test_c_tbs_enc_exp_mixed_statements());
}

TEST(tbs_enc_exp, cpp_mixed_statements) {
    ASSERT_TRUE(test_tbs_enc_exp_mixed_statements());
}

TEST(tbs_enc_exp, c_return_in_statement) {
    ASSERT_TRUE(test_c_tbs_enc_exp_return_in_statement());
}

TEST(tbs_enc_exp, cpp_return_in_statement) {
    ASSERT_TRUE(test_tbs_enc_exp_return_in_statement());
}
