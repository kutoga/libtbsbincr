# tbsenc

tbsenc is a very simple C/C++ library which allows you to achieve one thing: Make it for third-persons
hard do decompile or debug your code. How is this achieved? The library allow to apply a simple
encryption over a code section. The default mode is paranoid and safe: After each execution of
such an "important" section, the binary code is re-encrypted (with a new key). There might be
cases in which performance is very critical and for this reason you can configure each section
carefully. The created binary can be re-encrypted with new keys, therefore the binary can be
modified, but the functionality is the same.

## How to use it?

The two main macros are `tbs_enc` which can be applied to statements and `tbs_enc_exp` which
can be applied to expressions. All functions which contain such a section, must be marked with
`tbs_restricted_opt` (or alternatively multiple functions can be surrounded with `tbs_restricted_opt_begin`
and `tbs_restricted_opt_end`). This disable some very few optimizations which could cause problems.

```c
#include <stdio.h>
#include <tbsenc.h>

static tbs_restricted_opt int factorial(int n) {
    return 
}

```

## Development hints

tbsenc uses some tricks to achive its functionality. Unfortunately, this might produce some
weird compiler errors if you have syntax errors in an encrypted section. A solution to this
is, to compile the code with `-DTBS_ENC_DISABLE` to disable all encryptions. When you are done,
this flag can just be removed and all encryptions are applied. It is also possible to add this
flag before the include:

```c
#define TBS_ENC_DISABLE
#include <tbsenc.h>

...
```

To achive a optimal code size, it is recommended to pass all settings to a encrypted section
as compile time constant parameters. E.g. `tbs_enc_exp(..., _.thread_safe=false)` should be
prefered over `tbs_enc_exp(..., _.thread_safe=get_thread_safe_setting())`. Nevertheless, the
performance impact is not that big, but much more machine code will be generated to support
all possible configurations. Otherwise just one specific set of settings has to be supported.

The library might not work with all compilers / versions etc. But how can you know that?
The best solution is to just run all tests: `make check` will show if there are problems.
If you find any, please report them.

You might be interested how the library works and you even want to improve it. Then logs might
be helpful. If the library and the code it uses it is compiled with `-DTBS_LOG_ENABLE`, logs
are added. This can be very helpful.
