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

tbs_restrcited_opt_begin

/*
 * tbs_enc / tbs_enc_exp tests
 */

TEST(tbs_enc, section_tags) {
    int dummy = 0;
    const unsigned char head_opcode[] = _TBS_ENC_HEAD_OPCODE;
    const unsigned char foot_opcode[] = _TBS_ENC_FOOT_OPCODE;

    printf("start=%p\n", CODE_START);
    printf("end  =%p\n", CODE_END);
    printf("len  =%d\n", (int)CODE_LEN);

    CODE_START_MARKER;
    tbs_enc({
        dummy++; 
    }, _.re_encrypt=false);
    CODE_END_MARKER;

    printf("hey");

    unsigned char *head = _tbs_memmem(CODE_START, CODE_END, head_opcode, sizeof(head_opcode));
    unsigned char *foot = _tbs_memmem_reversed(CODE_START, CODE_END, foot_opcode, sizeof(foot_opcode));
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
    }, _.re_encrypt=true, _.re_enetrant=false);
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

enum t_protected_exp_action {
    PREPARE,
    CODE,
    RESET
};

static const char *protected_exp_action_to_string[] = {
    [PREPARE] = "PREPARE",
    [CODE]    = "CODE",
    [RESET]   = "RESET"
};

static std::string stringify_actions(const enum t_protected_exp_action *actions, int n_actions) {
    std::string res;
    for (int i = 0; i < n_actions; ++i) {
        if (i > 0) {
            res += ", ";
        }
        res += protected_exp_action_to_string[actions[i]];
    }
    return res;
}

#define ASSERT_ACTIONS_EQUAL(executed_actions, executed_actions_count, ...)                         \
_TBS_STMT_WRAPPER(({                                                                                 \
    const t_protected_exp_action actions[] = { __VA_ARGS__ };                                       \
    ASSERT_STREQ(stringify_actions(executed_actions, executed_actions_count).c_str(),                       \
                 stringify_actions(actions, _TBS_ARR_LEN(actions)).c_str());                                 \
}))

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

TEST(_tbs_protected_expression, re_enetrant_allows_recursive_calls) {
    const int n = 5;

    const int res = factorial(n);

    ASSERT_EQ(res, 120);
}

TEST(_tbs_protected_expression, without_auto_reset_prepares_once) {
    enum t_protected_exp_action actions[10];
    int actions_count = 0;

    const int dummy = _TBS_PROTECTED_EXPRESSION(0, ({
        if (actions_count < (int)_TBS_ARR_LEN(actions)) {
            actions[actions_count++] = CODE;
        }
        0;
    }), false, false, false, {
        if (actions_count < (int)_TBS_ARR_LEN(actions)) {
            actions[actions_count++] = PREPARE;
        }
    }, {
        if (actions_count < (int)_TBS_ARR_LEN(actions)) {
            actions[actions_count++] = RESET;
        }
    });

    ASSERT_EQ(dummy, 0);
    ASSERT_ACTIONS_EQUAL(actions, actions_count, PREPARE, CODE);
}

TEST(_tbs_protected_expression, without_auto_reset_prepares_once_when_multiple_times_executed) {
    enum t_protected_exp_action actions[10];
    int actions_count = 0;

    for (int i = 0; i < 2; ++i) {
        const int dummy = _TBS_PROTECTED_EXPRESSION(0, ({
            if (actions_count < (int)_TBS_ARR_LEN(actions)) {
                actions[actions_count++] = CODE;
            }
            0;
        }), false, false, false, {
            if (actions_count < (int)_TBS_ARR_LEN(actions)) {
                actions[actions_count++] = PREPARE;
            }
        }, {
            if (actions_count < (int)_TBS_ARR_LEN(actions)) {
                actions[actions_count++] = RESET;
            }
        });

        ASSERT_EQ(dummy, 0);
    }

    ASSERT_ACTIONS_EQUAL(actions, actions_count, PREPARE, CODE, CODE);
}

TEST(_tbs_protected_expression, auto_reset_resets) {
    enum t_protected_exp_action actions[10];
    int actions_count = 0;

    const int dummy = _TBS_PROTECTED_EXPRESSION(0, ({
        if (actions_count < (int)_TBS_ARR_LEN(actions)) {
            actions[actions_count++] = CODE;
        }
        0;
    }), false, false, true, {
        if (actions_count < (int)_TBS_ARR_LEN(actions)) {
            actions[actions_count++] = PREPARE;
        }
    }, {
        if (actions_count < (int)_TBS_ARR_LEN(actions)) {
            actions[actions_count++] = RESET;
        }
    });

    ASSERT_EQ(dummy, 0);
    ASSERT_ACTIONS_EQUAL(actions, actions_count, PREPARE, CODE, RESET);
}

TEST(_tbs_protected_expression, auto_reset_resets_always_when_multiple_times_executed) {
    enum t_protected_exp_action actions[10];
    int actions_count = 0;

    for (int i = 0; i < 2; ++i) {
        const int dummy = _TBS_PROTECTED_EXPRESSION(0, ({
            if (actions_count < (int)_TBS_ARR_LEN(actions)) {
                actions[actions_count++] = CODE;
            }
            0;
        }), false, false, true, {
            if (actions_count < (int)_TBS_ARR_LEN(actions)) {
                actions[actions_count++] = PREPARE;
            }
        }, {
            if (actions_count < (int)_TBS_ARR_LEN(actions)) {
                actions[actions_count++] = RESET;
            }
        });

        ASSERT_EQ(dummy, 0);
    }

    ASSERT_ACTIONS_EQUAL(actions, actions_count, PREPARE, CODE, RESET, PREPARE, CODE, RESET);
}

static int factorial2(int n, enum t_protected_exp_action *actions, int n_actions, int *actions_write_i) {
    return _TBS_PROTECTED_EXPRESSION(0, ({
        if (*actions_write_i < n_actions) {
            actions[(*actions_write_i)++] = CODE;
        }
        const int res = n <= 1 ? 1 : n * factorial2(n - 1, actions, n_actions, actions_write_i);
        res;
    }), true, false, true, {
        if (*actions_write_i < n_actions) {
            actions[(*actions_write_i)++] = PREPARE;
        }
    }, {
        if (*actions_write_i < n_actions) {
            actions[(*actions_write_i)++] = RESET;
        }
    });
}

TEST(_tbs_protected_expression, re_enetrant_resets_when_all_executions_are_finished) {
    enum t_protected_exp_action actions[10];
    int actions_count = 0;
    int n = 3;

    const int res = factorial2(n, actions, _TBS_ARR_LEN(actions), &actions_count);

    ASSERT_EQ(res, 6);
    ASSERT_ACTIONS_EQUAL(actions, actions_count, PREPARE, CODE, CODE, CODE, RESET);
}

tbs_restrcited_opt_end
