#ifndef __INTERNAL_TBS_CHECKSUM_H__
#define __INTERNAL_TBS_CHECKSUM_H__

#include <stdint.h>

#define TBS_CHECKSUM_INIT                       0xAA

static inline uint16_t tbs_checksum_next(uint16_t current, char value) {
    union {
        uint16_t checksum;
        char data[2];
    } byte_access = { .checksum = current };

    byte_access.data[0] ^= value;
    byte_access.data[1] += ~byte_access.data[0];
    byte_access.data[1] ^= value;

    return byte_access.checksum;
}

#endif
