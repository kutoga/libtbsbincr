# libtbsbincr

libtbsbincr is a C/C++ library which allows to obfuscate machine code for Windows and Linux
C/C++ program on x86/x64. It compiles without any problems with clang and gcc with the error flags -Wall -Wextra -Werror.

Everything can be compiled by just executing `make`. The target architecture can be defined with the `ARCH` flag.
E.g. `make ARCH=WIN32` or `make ARCH=WIN64` cross-compile the code for windows. `ARCH=local` uses the local architecture.
The resulting binaries are located in `bin/tbs/bincr`.

Below are some examples that show how this library can be used.

Take this code:
```c
unsigned fac_test(unsigned n) {
    unsigned res = 1;
    if (n >= 2) {
        res = n * fac_test(n -1);
    }
    return res;
}
```

For some reason you want to make it hard for third-persons to debug or analyze the machine code. Then you could do this:

```c
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


The library has many different obfuscation functions:
- Replace the obfuscated code only once at runtime and do not again obfuscate its machine code.
- Threadsafe or not threadsafe functions
- Easier to use macros for specific situations.
...

Now there are some examples:
```c
/*
 * If multiple encrypted (could be nested) sections are used, they require a number.
 * tbs_enc_code_ft_n is threadsafe.
 */
int TBS_UTIL_DISABLE_OPTIMIZATIONS test5(int a) {
    int res = a;
    tbs_enc_code_ft_n(0,
        res += a;
        tbs_enc_code_ft_n(1,
            res += a;
            tbs_enc_code_ft_n(2,
                res += a;
                tbs_enc_code_ft_n(3,
                    res += a;
                    
                    /* and so on... */
                    if (res < 20) {
                        tbs_enc_code_ft_n(4,
                            res += a;
                        );
                    }
                );
            );
        );
    );
    return res;
}

/* Also statements may be encrypted. These macros are not threadsafe. The threadsafe macros contain always "_ft_" int their name. */
int TBS_UTIL_DISABLE_OPTIMIZATIONS test6(int a, int b) {
    int res = 0;

    res += tbs_enc_stmt(a * b);
    
    /* A stmt is always like a enc_code, so if multiple stmts are mixed and also code (inside one function) then an index is needed. */
    tbs_enc_code_n(TBS_UTIL_COUNTER,
        res += tbs_enc_stmt_n(TBS_UTIL_COUNTER, a * b);
        res += tbs_enc_stmt_n(TBS_UTIL_COUNTER, a * b);
        res += tbs_enc_stmt_n(TBS_UTIL_COUNTER, a * b);
        
        /* "n" can still be provided. */
        res += tbs_enc_stmt_n(TBS_UTIL_COUNTER, a * b);
    );
    
    return res;
}

...
/* See example code files. */
```

If you like to see the log of the encryption etc. comment out this line in the Makefile:¨

`CFLAGS+=-DTBS_LOG_DISABLE`

There is an example tool which is called `crypt`. This tool allows to obfuscate comiled binaries or to unobfuscate them. Or also to re-obfuscate a binary with a new key.

````
./crypt -e example # encrypt / obfuscate
./crypt -d example # decrypt
./crypt -r example # re-obfuscate
````

All these function can also be used in the program itself. crypt is very easy and small, it shows how the API may be used. If you enable the log in the Makefile the crypt tool will shows many interesting details about which machine code has been changed to what code. It is important to know that your program if it is compiled, is NOT obfuscated. You first have to execute the crypt tool on it.

If you have any questions do not hesitate to contact me.
