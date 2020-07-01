#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/time.h>
#include <tbs/common.h>
#include <tbs/random.h>
#include "common.h"
#include "random.h"

static int tbs_random_time_based_next(struct tbs_random *rand) {
    unsigned number = _TBS_PTR_TO_UINT(rand->data);

    /* Mix in the time */
    struct timeval tv;
    gettimeofday(&tv, NULL);
    number ^= (unsigned)(tv.tv_usec + 1000000 * tv.tv_sec);

    number = tbs_random_next_linear(number);
    rand->data = _TBS_UINT_TO_PTR(number);
    return (int)number;
}

static void tbs_random_time_based_data_cleanup(struct tbs_random *rand) {
    _TBS_USE_VAR(rand);
}

tbs_random tbs_random_time_based = {
    .next = tbs_random_time_based_next,
    .data_cleanup = tbs_random_time_based_data_cleanup,
    .data = NULL
};
