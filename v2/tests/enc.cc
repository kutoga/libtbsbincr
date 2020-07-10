#include <gtest/gtest.h>
#include "enc_tests_c.h"
#include "enc_tests.h"

#define CODE_START_MARKER                               _TBS_LABEL(_code_start)
#define CODE_END_MARKER                                 _TBS_LABEL(_code_end)
#define CODE_START                                      (const unsigned char*)&&_code_start
#define CODE_END                                        (const unsigned char*)&&_code_end

static const unsigned char *c_memmem(const unsigned char *start_incl, const unsigned char *end_excl, const unsigned char *pattern, size_t pattern_size) {
    for (const unsigned char *curr = start_incl; curr + pattern_size < end_excl; ++curr) {
        if (!memcmp(curr, pattern, pattern_size)) {
            return curr;
        }
    }

    return NULL;
}

TEST(tbs_enc, encrypted_section_tags) {
    int dummy = 0;
    const unsigned char head_opcode[] = _TBS_ENC_HEAD_OPCODE;
    const unsigned char foot_opcode[] = _TBS_ENC_FOOT_OPCODE;

    CODE_START_MARKER;
    tbs_enc({
        dummy++; 
    });
    CODE_END_MARKER;

    const unsigned char *head = c_memmem(CODE_START, CODE_END, head_opcode, sizeof(head_opcode));
    const unsigned char *foot = c_memmem(CODE_START, CODE_END, foot_opcode, sizeof(foot_opcode));
    ASSERT_TRUE(head != nullptr);
    ASSERT_TRUE(foot != nullptr);
    ASSERT_LE(head, foot);
}

TEST(tbs_enc, encryption_changes_code) {
    ASSERT_FALSE(true);
}

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
