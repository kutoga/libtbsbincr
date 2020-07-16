#ifndef __TBS_ASM_H__
#define __TBS_ASM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

/*
 * A variable which is used to avoid some optimizations by the compiler.
 * It has a value of 0 and must never be overwritten.
 */
extern const volatile int _tbs_asm_always_zero;

/*
 * Assume you have the following code:
 * start:
 * asm volatile (
 *     ...
 * )
 * end:
 * ...
 * 
 * Without this dummy loop which accesses a volatile variable
 * it can (and will) happen that the address of "start" equals
 * the address of "end". This is due to optimizations done by
 * the compiler (moving the label is allowed if not goto is
 * available).
 * 
 * There is another solution which unfortunately only works
 * with new compilers:
 * https://stackoverflow.com/a/62757612/916672
 * asm goto(""::::label_name)
 * |-> This uses the label and avoids that the label is moved.
 */
#define _TBS_AVOID_LABEL_OPTIMIZATIONS(code)            \
_TBS_STMT_WRAPPER(do {                                  \
    code;                                               \
} while (_tbs_asm_always_zero))

/*
 * The head an foot assembler sequence has three requirements:
 * 1) It must not have any side effects. The code should do
 *    nothing.
 * 2) The code must create a non-trivial machine code sequence.
 *    (something like 0x000000... or 0x01010101... would be bad)
 *    They are used as head and foot tag in the binary code and
 *    despite some checks, we want to minimize the chance, to
 *    detect wrong heads / foots.
 * 3) The code must be big enough to hold the meta-data which
 *    is required for encryption (e.g. the key, checksums etc.).
 *    This is checked at compile time, so you cannot do this wrong.
 */

#ifdef __x86_64__

#define _TBS_ENC_HEAD_ASM                               \
asm volatile(                                           \
    "push %rax\n\t"                                     \
    "pop %rax\n\t"                                      \
    "push %rax\n\t"                                     \
    "nop\n\t"                                           \
    "nop\n\t"                                           \
    "nop\n\t"                                           \
    "pop %rax\n\t"                                      \
    "push %rax\n\t"                                     \
    "pop %rax\n\t"                                      \
)

#define _TBS_ENC_FOOT_ASM                               \
asm volatile(                                           \
    "push %rbx\n\t"                                     \
    "pop %rbx\n\t"                                      \
    "push %rbx\n\t"                                     \
    "nop\n\t"                                           \
    "pop %rbx\n\t"                                      \
    "push %rbx\n\t"                                     \
    "pop %rbx\n\t"                                      \
)

#else

#define _TBS_ENC_HEAD_ASM                               \
asm volatile(                                           \
    "push %rax\n\t"                                     \
    "pop %rax\n\t"                                      \
    "push %rax\n\t"                                     \
    "nop\n\t"                                           \
    "nop\n\t"                                           \
    "nop\n\t"                                           \
    "pop %rax\n\t"                                      \
    "push %rax\n\t"                                     \
    "pop %rax\n\t"                                      \
)

#define _TBS_ENC_FOOT_ASM                               \
asm volatile(                                           \
    "push %ebx\n\t"                                     \
    "pop %ebx\n\t"                                      \
    "push %ebx\n\t"                                     \
    "nop\n\t"                                           \
    "pop %ebx\n\t"                                      \
    "push %ebx\n\t"                                     \
    "pop %ebx\n\t"                                      \
)

#endif

#define _TBS_ENC_HEAD                                   \
_TBS_AVOID_LABEL_OPTIMIZATIONS(_TBS_ENC_HEAD_ASM)

#define _TBS_ENC_FOOT                                   \
_TBS_AVOID_LABEL_OPTIMIZATIONS(_TBS_ENC_FOOT_ASM)

/*
 * TODO: Autogenerate (currently used: https://defuse.ca/online-x86-assembler.htm#disassembly ) 
 * Fortunately the code is exactely the same for 32 and 64 bit:)
 */
#define _TBS_ENC_HEAD_OPCODE                                { 0x50, 0x58, 0x50, 0x90, 0x90, 0x90, 0x58, 0x50, 0x58 }
#define _TBS_ENC_HEAD_LEN                                   _TBS_ARR_LEN((const unsigned char[])_TBS_ENC_HEAD_OPCODE)
#define _TBS_ENC_FOOT_OPCODE                                { 0x53, 0x5B, 0x53, 0x90, 0x5B, 0x53, 0x5B }
#define _TBS_ENC_FOOT_LEN                                   _TBS_ARR_LEN((const unsigned char[])_TBS_ENC_FOOT_OPCODE)

const unsigned char *_tbs_find__head(const char *start, const char *end);



#ifdef __cplusplus
}
#endif

#endif
