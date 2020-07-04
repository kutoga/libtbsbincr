#ifndef __INTERNAL_TBS_COMMON_H__
#define __INTERNAL_TBS_COMMON_H__

#include <assert.h>

/*
 * For some structs which have userdata, which is usually a "void *", we might
 * avoid a malloc if we just have to store a number. Assuming it is an unsigned
 * int, the following macros might be used.
 */

typedef union _tbs_uint_ptr_convert {
    unsigned number;
    void *ptr;
}  _tbs_uint_ptr_convert;

static_assert(
    sizeof((_tbs_uint_ptr_convert){}.ptr) >= sizeof((_tbs_uint_ptr_convert){}.number),
    "Require to have a pointer size larger or equal to an unsigned int for a hacky storage!"
);

#define _TBS_UINT_TO_PTR(value)             ((_tbs_uint_ptr_convert) { .number = (value) }).ptr

#define _TBS_PTR_TO_UINT(ptr_value)         ((_tbs_uint_ptr_convert) { .ptr = (ptr_value) }).number

#endif
