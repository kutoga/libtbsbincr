#ifndef __TBS_CRYPTO_ALGORITHM_H__
#define __TBS_CRYPTO_ALGORITHM_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tbs_crypto_algorithm {
    char (*encrypt)(struct tbs_crypto_algorithm *alg, char chr);
    char (*decrypt)(struct tbs_crypto_algorithm *alg, char chr);
    void (*data_cleanup)(struct tbs_crypto_algorithm *alg);
    void *data;
} tbs_crypto_algorithm;

typedef void (*tbs_crypto_algorithm_initializer)(struct tbs_crypto_algorithm *target, int key);

void tbs_crypto_algorithm_simple_init(struct tbs_crypto_algorithm *target, int key);

void tbs_crypto_algorithm_none_init(struct tbs_crypto_algorithm *target, int key);

#ifdef __cplusplus
}
#endif

#endif
