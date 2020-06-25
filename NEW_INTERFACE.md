# new interface for V2

```cpp
// thread safe
static int my_func(int a) {
    int b = 0;
    tbs_enc(
        b += a;
        b *= a;
    );
    return b;
}

// not thread safe
static int my_func(int a) {
    int b = 0;
    tbs_enc({
        b += a;
        b *= a;
    }, thread_safe: false);
    return b;
}

// expression
static int my_func(int a) {
    int b = tbs_enc_exp(a * a, thread_safe: false);
    return b;
}

// Multiple tbs_enc are supported in the same function; also nested is ok
static int my_func(int a) {
    int b = tbs_enc_exp(0);
    tbs_enc(
        b += 1;
    );
    tbs_enc(
        b *= tbs_enc_exp(a);
    );
}
```

What settings do exist?
- `thread_safe`: If enabled, locking will be used
- `auto_encrypt` (naming?): Automatically re-encrypt after the code is outside of the section
- `keygen`: The used key-generator
- `settings`: Base settings (tbs_enc_config)

