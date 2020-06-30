#ifndef __TBS_COMMON_H__
#define __TBS_COMMON_H__

/*
 * Wrap a piece of code into a statement. Mostly used to avoid writing
 * all the time "do { ... } while (0)"
 */
#define _TBS_STMT_WRAPPER(code)                                             do { code; } while (0)

/*
 * An empty / placeholder statement.
 */
#define _TBS_STMT_EMPTY                                                     _TBS_STMT_WRAPPER()

/*
 * Avoid unused variable warning: Dummy use a variable.
 */
#define _TBS_USE_VAR(var)                                                   (void)(var)

/*
 * Generate a symbol name: Use a given number, an identifier
 * and create a likely unique name.
 */
#define _TBS_SYM_NAME(n, name)                                             _tbs_ ## n ## __ ## name

/*
 * Is the current compiler GCC?
 */
#if defined(__GNUC__) && !defined(__clang__)
#define _TBS_IS_GCC
#endif

/*
 * Create a label; already place a valid dummy / empty statement after the label,
 * so the label can be defined anywhere.
 */
#define _TBS_LABEL(label_name)                                              \
_TBS_STMT_WRAPPER(                                                          \
    label_name:                                                             \
    _TBS_STMT_EMPTY;                                                        \
)

/*
 * Create a macro which wraps an expression and allow old gnu style struct
 * initialization in this expression and overriding values. E.g.
 * struct x = {
 *  name: "hey",
 *  name: "you",
 *  age: 29,
 * }
 * is perfectly valid in this context. This macro is mainly useful for
 * optional function parameters.
 */
#ifdef _TBS_IS_GCC

/*
 * gcc (at least v7.5) has buggy behaviour with the more general
 * _Pragma version that works with gcc and clang. In situations where
 * this macro is used multiple times, it might miss-place the _Pragmas.
 * Other compilers, like clang, work perfectly fine.
 * 
 * For this reason, there is one version which is only used with gcc.
 */
#define _TBS_STRUCT_IGNORE_OVERRIDE_EXP(expression)                         \
({                                                                          \
    _Pragma("GCC diagnostic push")                                          \
    _Pragma("GCC diagnostic ignored \"-Woverride-init\"")                   \
    (expression);                                                           \
    _Pragma("GCC diagnostic pop")                                           \
})

#else

#define _TBS_STRUCT_IGNORE_OVERRIDE_EXP(expression)                         \
({                                                                          \
    _Pragma("GCC diagnostic push")                                          \
    _Pragma("GCC diagnostic ignored \"-Wunknown-warning-option\"")          \
    _Pragma("GCC diagnostic ignored \"-Woverride-init\"")                   \
    _Pragma("GCC diagnostic ignored \"-Winitializer-overrides\"")           \
    _Pragma("GCC diagnostic ignored \"-Wgnu-designator\"")                  \
    (expression);                                                           \
    _Pragma("GCC diagnostic pop")                                           \
})

#endif

#endif
