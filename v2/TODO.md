C++ does not the optional argumen initialization:
```c
int x = 2;
int y = tbs_enc_exp(x * x, thread_safe: false, re_encrypt: false);
```

So we have to uglify the initialization:
```c
int x = 2;
int y = tbs_enc_exp(x * x, _.thread_safe=false, _.re_encrypt=false);
```

This is not as nice, but it works well with C and C++.
