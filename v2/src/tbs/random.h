#ifndef __INTERNAL_TBS_RANDOM_H__
#define __INTERNAL_TBS_RANDOM_H__

static inline int tbs_random_next_linear(int seed) {
    unsigned data = (unsigned)seed;

    /* Based on http://stackoverflow.com/a/11946674/916672 */
    data = (data * 1103515245U + 12345U) & 0x7fffffffU;

    return (int)data;
}

#endif