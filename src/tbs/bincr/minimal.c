#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <tbs/bincr/minimal.h>
#include <tbs/bincr/platform.h>
#include <tbs/log/core.h>

/*
 * In the resulting binary there must not be the head opcode and the foot opcode,
 * except for the encrypted code pieces. So unfortunately it is not possible
 * to just create two constants. This is a bit hacky, but it works:)
 *
 * This code assumes that the first byte of the opcode (head and foot) is not zero.
 */

const unsigned char *tbs_bincr_enc_head_opcode(void) {
    static unsigned char head_opcode[sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR)] = { 0x00 };
    if (!head_opcode[0]) {
        const unsigned char tmp[sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR)] = TBS_BINCR_ENC_HEAD_OPCODE;
        memcpy(head_opcode, tmp, sizeof(tmp));
    }
    return head_opcode;
}

const unsigned char *tbs_bincr_enc_foot_opcode(void) {
    static unsigned char foot_opcode[sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR)] = { 0x00 };
    if (!foot_opcode[0]) {
        const unsigned char tmp[sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR)] = TBS_BINCR_ENC_FOOT_OPCODE;
        memcpy(foot_opcode, tmp, sizeof(tmp));
    }
    return foot_opcode;
}

int tbs_bincr_decrypt(void *section, int change_access_rights) {
    unsigned char *body = (unsigned char *)section;
    tbs_log_trace("Enter section: %p", section);
    
    /* Nothing to do. */
    if (TBS_BINCR_IS_DECRYPTED(*body)) {
        tbs_log_trace("The section %p is already decrypted.", section);
        return 1;
    }
    
    /* Valid encryption head? */
    if (!TBS_BINCR_IS_ENCRYPTED(*body)) {
        tbs_log_warn("The section %p cannot be parsed.", section);
        return -1;
    }
    
    /* Parse the key and the body length */
    tbs_log_trace("The section %p is encrypted.", section);
    assert(sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR) >= 5);
    uint16_t key = ((uint16_t)body[1] << 8) + (uint16_t)body[2];
    uint16_t len = ((uint16_t)body[3] << 8) + (uint16_t)body[4];
    len ^= key;
    tbs_log_trace("The section %p uses the initial key 0x%04X and has a code length of %ul bytes.", section, key, len);
    unsigned int total_len = len + sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR) + sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR);
    
    if (change_access_rights) {
    
        /* Now we have to edit the code section. For this we need some rights. */
        tbs_encr_rwx(body, len + sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR));
    }

    /* Rewrite the header. */
    memcpy(body, tbs_bincr_enc_head_opcode(), sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR));
    
    /* Decrypt the body. */
    tbs_log_trace("Decrypt %p...", section);
    unsigned int i;
    for (i = sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR); i < total_len; i++) {
        body[i] ^= tbs_bincr_next_key_byte(&key);
    }
    
    if (change_access_rights) {
    
        /* Reset the rights. */
        tbs_encr_rx(body, total_len);
    }
    
    tbs_log_trace("The section %p is now decrypted.", section);
    
    return 0;
}


