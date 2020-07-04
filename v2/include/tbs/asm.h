#ifndef __TBS_ASM_H__
#define __TBS_ASM_H__

#include "common.h"

static inline void __attribute__((always_inline)) _TBS_ENC_HEAD() {
    _TBS_DISABLE_OPTIMIZATIONS({
        __asm__ __volatile__(
#if __x86_64__
            ".code64\n\t"
            "push %rax\n\t"
            "push %rax\n\t"
            "nop\n\t"
            "pop %rax\n\t"
            "pop %rax\n\t"
#else
            ".code32\n\t"
            "push %eax\n\t"
            "push %eax\n\t"
            "nop\n\t"
            "pop %eax\n\t"
            "pop %eax\n\t"
#endif
        );
    });
}


static inline void __attribute__((always_inline)) TBS_ENC_FOOT() {
    _TBS_DISABLE_OPTIMIZATIONS({
        __asm__ __volatile__(
#if __x86_64__
            ".code64\n\t"
            "push %rbx\n\t"
            "push %rbx\n\t"
            "nop\n\t"
            "pop %rbx\n\t"
            "pop %rbx\n\t"
#else
            ".code32\n\t"
            "push %ebx\n\t"
            "push %ebx\n\t"
            "nop\n\t"
            "pop %ebx\n\t"
            "pop %ebx\n\t"
#endif
        );
    });
}


/*
 * TODO: Autogenerate (currently used: https://defuse.ca/online-x86-assembler.htm#disassembly ) 
 * Or at least add a test which checks if the opcode is correct, that is actually quite trivial.
 * Fortunately the code is exactely the same for 32 and 64 bit:)
 */
#define _TBS_ENC_HEAD_OPCODE                                ((unsigned char[]) { 0x50, 0x50, 0x90, 0x58, 0x58 })
#define _TBS_ENC_FOOT_OPCODE                                ((unsigned char[]) { 0x53, 0x53, 0x90, 0x5B, 0x5B })

#endif
