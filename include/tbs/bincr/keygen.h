#ifndef __TBS_ENCR_KEYGEN_H__
#define __TBS_ENCR_KEYGEN_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef struct tbs_bincr_key_gen_t  {
    void (*seed)(struct tbs_bincr_key_gen_t *, int);
    uint16_t (*next)(struct tbs_bincr_key_gen_t *);
    void (*data_cleanup)(struct tbs_bincr_key_gen_t *);
    void *data;
} tbs_bincr_key_gen_t;

void tbs_bincr_key_gen_seed(tbs_bincr_key_gen_t *key_gen, int seed);

uint16_t tbs_bincr_key_gen_next(tbs_bincr_key_gen_t *key_gen);

void tbs_bincr_key_gen_delete(tbs_bincr_key_gen_t *key_gen);

tbs_bincr_key_gen_t *tbs_bincr_key_gen_default_impl_new(void);

#ifdef __cplusplus
}
#endif

#endif /* __TBS_ENCR_KEYGEN_H__ */

