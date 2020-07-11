#include <gtest/gtest.h>
#include <tbs/common.h>
#include "enc_tests_c.h"
#include "enc_tests.h"

#define CODE_START_MARKER                               _TBS_LABEL(_code_start)
#define CODE_END_MARKER                                 _TBS_LABEL(_code_end)
#define CODE_START                                      (unsigned char*)&&_code_start
#define CODE_END                                        (unsigned char*)&&_code_end
#define CODE_LEN                                        (CODE_END - CODE_START)

TEST(tbs_enc, encrypted_section_tags) {
    int dummy = 0;
    const unsigned char head_opcode[] = _TBS_ENC_HEAD_OPCODE;
    const unsigned char foot_opcode[] = _TBS_ENC_FOOT_OPCODE;

    CODE_START_MARKER;
    tbs_enc({
        dummy++; 
    });
    CODE_END_MARKER;

    unsigned char *head = _tbs_memmem(CODE_START, CODE_END, head_opcode, sizeof(head_opcode));
    unsigned char *foot = _tbs_memmem(CODE_START, CODE_END, foot_opcode, sizeof(foot_opcode));
    ASSERT_TRUE(head != nullptr);
    ASSERT_TRUE(foot != nullptr);
    ASSERT_LE(head, foot);
}

TEST(tbs_enc, encryption_changes_code) {
    int dummy = 0;
    char *code_before = (char *)malloc(CODE_LEN);
    char *code_after = (char *)malloc(CODE_LEN);
    memcpy((void *)code_before, (void *)CODE_START, CODE_LEN);

    CODE_START_MARKER;
    tbs_enc({
        dummy++; 
    }, _.re_encrypt=true);
    CODE_END_MARKER;

    memcpy((void *)code_after, (void *)CODE_START, CODE_LEN);
    EXPECT_TRUE(memcmp(code_before, code_after, CODE_LEN) != 0);
    free(code_before);
    free(code_after);
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
