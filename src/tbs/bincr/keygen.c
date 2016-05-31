#include <stdlib.h>
#include <tbs/bincr/keygen.h>

#define TBS_BINCR_KEY_GEN_DEFAULT_INIT_SEED                 1

/* Copied from http://stackoverflow.com/a/11946674/916672 */
static void tbs_bincr_key_gen_default_seed(tbs_bincr_key_gen_t *key_gen, int seed) {
    *(unsigned *)key_gen->data = (unsigned)seed & 0x7fffffffU;
}

/* Copied from http://stackoverflow.com/a/11946674/916672 */
static uint16_t tbs_bincr_key_gen_default_next(tbs_bincr_key_gen_t *key_gen) {
    unsigned *seed = (unsigned *)key_gen->data;
    (*seed) = ((*seed) * 1103515245U + 12345U) & 0x7fffffffU;
    return (uint16_t)*seed;
}

static void tbs_bincr_key_gen_default_data_cleanup(tbs_bincr_key_gen_t *key_gen) {
    free(key_gen->data);
}

void tbs_bincr_key_gen_seed(tbs_bincr_key_gen_t *key_gen, int seed) {
    key_gen->seed(key_gen, seed);
}

uint16_t tbs_bincr_key_gen_next(tbs_bincr_key_gen_t *key_gen) {
    return key_gen->next(key_gen);
}

void tbs_bincr_key_gen_delete(tbs_bincr_key_gen_t *key_gen) {
    key_gen->data_cleanup(key_gen);
    free(key_gen);
}

tbs_bincr_key_gen_t *tbs_bincr_key_gen_default_impl_new(void) {
    tbs_bincr_key_gen_t *key_gen = (tbs_bincr_key_gen_t *)malloc(sizeof(*key_gen));
    key_gen->seed = tbs_bincr_key_gen_default_seed;
    key_gen->next = tbs_bincr_key_gen_default_next;
    key_gen->data_cleanup = tbs_bincr_key_gen_default_data_cleanup;
    key_gen->data = malloc(sizeof(unsigned));
    *(unsigned *)key_gen->data = TBS_BINCR_KEY_GEN_DEFAULT_INIT_SEED;
    return key_gen;
}


