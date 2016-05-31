# libtbsbincr

libtbsbincr is a C/C++ library which allows to obfuscate machine code for Windows and Linux
C/C++ program on x86/x64.

Take this code:
```
unsigned fac_test(unsigned n) {
    unsigned res = 1;
    if (n >= 2) {
        res = n * fac_test(n -1);
    }
    return res;
}
```

For some reason you want to make it hard for third-persons to debug or analyze the machine code. Then you could do this:

```
unsigned TBS_UTIL_DISABLE_OPTIMIZATIONS fac_test(unsigned n) {
    unsigned res = 1;
    tbs_enc_code_ft(
        if (n >= 2) {
            res = n * fac_test(n -1);
        }
    );
    return res;
}
```

Every function which contains obfuscated code should use the TBS_UTIL_DISABLE_OPTIMIZATIONS macro (see example3.c for explanation). The obfuscated code itself is inside of tbs_enc_code_ft. At runtime at the code position is just crap and as soon as the code is executed it is replaced by the real machine code. After the code is executed it will be obfuscasted again by a new key. Also binary files always can be reobfuscated which means the code will be "encrpyted" with a new key.

