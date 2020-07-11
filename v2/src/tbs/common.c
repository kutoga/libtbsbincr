#include <string.h>
#include <tbs/common.h>

unsigned char *_tbs_memmem(unsigned char *start_incl, unsigned char *end_excl, const unsigned char *pattern, size_t pattern_size) {
    for (unsigned char *curr = start_incl; curr + pattern_size < end_excl; ++curr) {
        if (!memcmp(curr, pattern, pattern_size)) {
            return curr;
        }
    }

    return NULL;
}

unsigned char *_tbs_memmem_reversed(unsigned char *start_incl, unsigned char *end_excl, const unsigned char *pattern, size_t pattern_size) {
    for (unsigned char *curr = end_excl - pattern_size; curr >= start_incl; --curr) {
        if (!memcmp(curr, pattern, pattern_size)) {
            return curr;
        }
    }

    return NULL;
}