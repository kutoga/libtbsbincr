#include <gtest/gtest.h>
#include <tbs/common.h>
#include <tbs/asm.h>

#define CODE_START_MARKER                               _TBS_LABEL(_code_start)
#define CODE_END_MARKER                                 _TBS_LABEL(_code_end)
#define CODE_START                                      (unsigned char*)&&_code_start
#define CODE_END                                        (unsigned char*)&&_code_end
#define CODE_LEN                                        (CODE_END - CODE_START)


TEST(tbs_enc_head, head_enc_len) {
    const unsigned char tbs_enc_head_opcode[] = _TBS_ENC_HEAD_OPCODE;

    ASSERT_EQ(_TBS_ARR_LEN(tbs_enc_head_opcode), _TBS_ENC_HEAD_LEN);
}


TEST(tbs_enc_head, op_code) {
    const unsigned char tbs_enc_head_opcode[] = _TBS_ENC_HEAD_OPCODE;
    CODE_START_MARKER;
    _TBS_ENC_HEAD;
    CODE_END_MARKER;

    const unsigned char *opcode_bytes = CODE_START;
    size_t opcode_len = CODE_LEN;

    ASSERT_GE(opcode_len, _TBS_ENC_HEAD_LEN);
    ASSERT_TRUE(!memcmp(opcode_bytes, tbs_enc_head_opcode, _TBS_ENC_HEAD_LEN));
}


TEST(tbs_enc_foot, foot_enc_len) {
    const unsigned char tbs_enc_foot_opcode[] = _TBS_ENC_FOOT_OPCODE;

    ASSERT_EQ(_TBS_ARR_LEN(tbs_enc_foot_opcode), _TBS_ENC_FOOT_LEN);
}


TEST(tbs_enc_foot, op_code) {
    const unsigned char tbs_enc_foot_opcode[] = _TBS_ENC_FOOT_OPCODE;
    CODE_START_MARKER;
    _TBS_ENC_FOOT;
    CODE_END_MARKER;

    const unsigned char *opcode_bytes = CODE_START;
    size_t opcode_len = CODE_LEN;

    ASSERT_GE(opcode_len, _TBS_ENC_FOOT_LEN);
    ASSERT_TRUE(!memcmp(opcode_bytes, tbs_enc_foot_opcode, _TBS_ENC_FOOT_LEN));
}


TEST(tbs_avoid_label_optimizations, overhead) {
    CODE_START_MARKER;
    _TBS_AVOID_LABEL_OPTIMIZATIONS();
    CODE_END_MARKER;

    size_t overhead = CODE_LEN;

    ASSERT_GT(overhead, 0) << "The avoid label optimizations should create some overhead";
    ASSERT_LT(overhead, 20) << "The overhead should be less than 20 bytes";
}
