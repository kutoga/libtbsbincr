#include <gtest/gtest.h>
#include <tbs/common.h>
#include "enc_tests_c.h"
#include "enc_tests.h"

#define CODE_START_MARKER                               _TBS_LABEL(_code_start)
#define CODE_END_MARKER                                 _TBS_LABEL(_code_end)
#define CODE_START                                      (unsigned char*)&&_code_start
#define CODE_END                                        (unsigned char*)&&_code_end
#define CODE_LEN                                        (CODE_END - CODE_START)

#define FOR_EACH_BOOL(var, code)                        \
_TBS_STMT_WRAPPER(({                                     \
    const bool values[] = {true, false};                               \
    for (int _i = 0; _i < (int)_TBS_ARR_LEN(values); ++_i) { \
        bool var = values[_i];                           \
        code;                                           \
    }                                                   \
}))

/*
 * tbs_enc / tbs_enc_exp tests
 */

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

/*
 * Some tests which are done in C and C++
 */

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

/*
 * _TBS_PROTECTED_EXPRESSION tests
 */

TEST(_tbs_protected_expression, expression_evaluates) {
    const int expression_res = 12;

    const int result = _TBS_PROTECTED_EXPRESSION(0, {
        expression_res;
    }, false, false, false, _TBS_STMT_EMPTY, _TBS_STMT_EMPTY);

    ASSERT_EQ(result, expression_res);
}

TEST(_tbs_protected_expression, serial_execution_expression_evaluates_for_all_configs) {
    const int expression_res = 12;

    FOR_EACH_BOOL(re_enetrant, {
    FOR_EACH_BOOL(thread_safe, {
    FOR_EACH_BOOL(auto_reset, {
        const int result = _TBS_PROTECTED_EXPRESSION(0, ({
            expression_res;
        }), re_enetrant, thread_safe, auto_reset, _TBS_STMT_EMPTY, _TBS_STMT_EMPTY);

        ASSERT_EQ(result, expression_res);
    });});});
}

static int factorial(int n) {
    return _TBS_PROTECTED_EXPRESSION(0, ({
        n <= 1 ? 1 : n * factorial(n - 1);
    }), true, false, false, _TBS_STMT_EMPTY, _TBS_STMT_EMPTY);
}

TEST(_tbs_protected_expression, _re_enetrant_allows_recursive_calls) {
    const int n = 5;

    const int res = factorial(n);

    ASSERT_EQ(res, 120);
}

TEST(_tbs_protected_expression, _auto_reset_resets) {
    enum { CODE, PREPARE, RESET } actions[10];
    int action_count = 0;

    const int dummy = _TBS_PROTECTED_EXPRESSION(0, ({
        if (action_count < (int)_TBS_ARR_LEN(actions)) {
            actions[action_count++] = CODE;
        }
        0;
    }), false, false, true, {
        if (action_count < (int)_TBS_ARR_LEN(actions)) {
            actions[action_count++] = PREPARE;
        }
    }, {
        if (action_count < (int)_TBS_ARR_LEN(actions)) {
            actions[action_count++] = RESET;
        }
    });

    ASSERT_EQ(dummy, 0);
    ASSERT_EQ(action_count, 3);
    ASSERT_EQ(actions[0], PREPARE);
    ASSERT_EQ(actions[1], CODE);
    ASSERT_EQ(actions[2], RESET);
}
