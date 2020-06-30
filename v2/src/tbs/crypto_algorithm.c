#include <tbs/crypto_algorithm.h>

void tbs_crypto_algorithm_simple_init(struct tbs_crypto_algorithm *target, int key) {
}

/*
 * "None" encryption algorithm. Mainly used for testing.
 */

static char tbs_crypto_algorithm_none_identity(struct tbs_crypto_algorithm *alg, char chr) {
    return chr;
}

static void tbs_crypto_algorithm_none_data_cleanup(struct tbs_crypto_algorithm *alg) {
}

void tbs_crypto_algorithm_none_init(struct tbs_crypto_algorithm *target, int key) {
    target->encrypt = tbs_crypto_algorithm_none_identity;
    target->decrypt = tbs_crypto_algorithm_none_identity;
    target->data_cleanup = tbs_crypto_algorithm_none_data_cleanup;
    target->data = NULL;
}
