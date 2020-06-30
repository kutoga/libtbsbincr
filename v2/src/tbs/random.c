#include <tbs/random.h>

static int tbs_random_time_based_next(struct tbs_random *rand) {
    1
}

static void tbs_random_time_based_data_cleanup(struct tbs_random *rand) {
}

tbs_random tbs_random_time_based = {
    .next = tbs_random_time_based_next,
    .data_cleanup = tbs_random_time_based,
    .data = NULL
};
