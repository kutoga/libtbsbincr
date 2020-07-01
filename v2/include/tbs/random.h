#ifndef __TBS_RANDOM_H__
#define __TBS_RANDOM_H__

typedef struct tbs_random {
    int (*next)(struct tbs_random *rand);
    void (*data_cleanup)(struct tbs_random *rand);
    void *data;
} tbs_random;

extern tbs_random tbs_random_time_based;

#endif
