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
 * __asm__ __volatile__ (
 *     ...
 * )
 * end:
 * ...
 * 
 * Without this dummy loop which accesses a volatile variable
 * it can (and will) happen that the address of "start" equals
 * the address of "end". I don't know why, but the loop is a
 * solution without much overhead.
 */
#define _TBS_AVOID_LABEL_OPTIMIZATIONS(code)            \
_TBS_STMT_WRAPPER(do {                                  \
    code;                                               \
} while (_tbs_asm_always_zero))

#ifdef __x86_64__

#define _TBS_ENC_HEAD_ASM                               \
__asm__ __volatile__(                                   \
    ".code64\n\t"                                       \
    "push %rax\n\t"                                     \
    "push %rax\n\t"                                     \
    "nop\n\t"                                           \
    "pop %rax\n\t"                                      \
    "pop %rax\n\t"                                      \
)

#define _TBS_ENC_FOOT_ASM                               \
__asm__ __volatile__(                                   \
    ".code64\n\t"                                       \
    "push %rbx\n\t"                                     \
    "push %rbx\n\t"                                     \
    "nop\n\t"                                           \
    "pop %rbx\n\t"                                      \
    "pop %rbx\n\t"                                      \
)

#else

#define _TBS_ENC_HEAD_ASM                               \
__asm__ __volatile__(                                   \
    ".code32\n\t"                                       \
    "push %rax\n\t"                                     \
    "push %rax\n\t"                                     \
    "nop\n\t"                                           \
    "pop %rax\n\t"                                      \
    "pop %rax\n\t"                                      \
)

#define _TBS_ENC_FOOT_ASM                               \
__asm__ __volatile__(                                   \
    ".code32\n\t"                                       \
    "push %ebx\n\t"                                     \
    "push %ebx\n\t"                                     \
    "nop\n\t"                                           \
    "pop %ebx\n\t"                                      \
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
#define _TBS_ENC_HEAD_OPCODE                                { 0x50, 0x50, 0x90, 0x58, 0x58 }
#define _TBS_ENC_HEAD_LEN                                   _TBS_ARR_LEN((const unsigned char[])_TBS_ENC_HEAD_OPCODE)
#define _TBS_ENC_FOOT_OPCODE                                { 0x53, 0x53, 0x90, 0x5B, 0x5B }
#define _TBS_ENC_FOOT_LEN                                   _TBS_ARR_LEN((const unsigned char[])_TBS_ENC_FOOT_OPCODE)

#ifdef __cplusplus
}
#endif

#endif
