#include <stdlib.h>
#include <tbs/common.h>
#include <tbs/crypto_algorithm.h>
#include "common.h"
#include "random.h"

static void tbs_crypto_algorithm_no_data_cleanup(struct tbs_crypto_algorithm *alg) {
    _TBS_USE_VAR(alg);
}

static char tbs_crypto_algorithm_simple_next(struct tbs_crypto_algorithm *target, char chr) {
    int number = (unsigned)_TBS_PTR_TO_UINT(target->data);
    number = tbs_random_next_linear(number);
    const char key = (char)number;
    target->data = _TBS_UINT_TO_PTR((unsigned)number);
    return chr ^ key;
}

void tbs_crypto_algorithm_simple_init(struct tbs_crypto_algorithm *target, int key) {
    target->encrypt = tbs_crypto_algorithm_simple_next;
    target->decrypt = tbs_crypto_algorithm_simple_next;
    target->data_cleanup = tbs_crypto_algorithm_no_data_cleanup;
    target->data = _TBS_UINT_TO_PTR((unsigned)key);
}

/*
 * "None" encryption algorithm. Mainly used for testing.
 */

static char tbs_crypto_algorithm_none_identity(struct tbs_crypto_algorithm *alg, char chr) {
    _TBS_USE_VAR(alg);
    return chr;
}

void tbs_crypto_algorithm_none_init(struct tbs_crypto_algorithm *target, int key) {
    _TBS_USE_VAR(key);
    target->encrypt = tbs_crypto_algorithm_none_identity;
    target->decrypt = tbs_crypto_algorithm_none_identity;
    target->data_cleanup = tbs_crypto_algorithm_no_data_cleanup;
    target->data = NULL;
}
