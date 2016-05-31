#include <stdlib.h>
#include <string.h>
#include <tbs/bincr/platform.h>
#include <tbs/bincr/core.h>
#include <tbs/log/core.h>

#ifdef TBS_BINCR_DISABLE_LIBENC
#define tbs_bincr_enc_code_ft(code)             TBS_UTIL_STATEMENT_WRAPPER(code)
#define tbs_bincr_no_optimizations              
#else
#define tbs_bincr_enc_code_ft(code)             tbs_enc_code_ft(code)
#define tbs_bincr_no_optimizations              TBS_UTIL_DISABLE_OPTIMIZATIONS
#endif

#define tbs_bincr_enc_code(code)                tbs_bincr_enc_code_ft(code)

#if !defined(WIN32) && !defined(__clang__)
/*
 * Some versions of gcc produce errors without this hack (e.g. my local ones v4.6.4 and v5.3.1)
 * See: https://stackoverflow.com/questions/34907503/gcc-fread-chk-warn-warning
 */
static size_t __attribute__((noinline)) tbs_fread_wrapper(void *ptr, size_t size, size_t count, FILE *stream) {
    return fread(ptr, size, count, stream);
}
#define fread(ptr, size, count, stream)         tbs_fread_wrapper((ptr), (size), (count), (stream))
#endif

int tbs_bincr_no_optimizations tbs_bincr_generate_file_seed(FILE *file) {
    int seed = 0x12345678;
    tbs_bincr_enc_code(
        long int pos = ftell(file);
        fseek(file, 0, SEEK_SET);
        int tmp;
        while (fread(&tmp, sizeof(tmp), 1, file) == 1) {
            seed ^= tmp;
        
            /* Copied from http://stackoverflow.com/a/11946674/916672 */
            seed = (seed * 1103515245U + 12345U * tmp) & 0x7fffffffU;
        }
        fseek(file, pos, SEEK_SET);
        tbs_log_trace("Generated the seed %d from a file.", seed);
    );
    return seed;
}

int tbs_bincr_generate_section_seed(void *section, void *end_flag) {
    /* This function must not be encrypted, because it is required for thread-safe de/encryption. */

    int seed = 0;
    const unsigned char *begin = (unsigned char *)section;
    const unsigned char *end = (unsigned char *)end_flag;
    const unsigned char *curr;
    end += sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR);

    seed = (begin - end) * 0xFFFFFFFF;
    char *seed_acc = (char *)&seed;
    int seed_i = 0;
    for (curr = begin; curr < end; curr++, seed_i = (seed_i + 1) % sizeof(seed)) {
        seed_acc[seed_i] ^= *curr;
	    
        /* Copied from http://stackoverflow.com/a/11946674/916672 */
        seed = (seed * 1103515245U + 12345U * (*curr)) & 0x7fffffffU;
    }

    tbs_log_trace("Generated the seed %d from the section %p.", seed, section);
    return seed;
}

/* Direction = 1 => downwards, Direction = 0 => upwards */
static long int tbs_bincr_no_optimizations tbs_bincr_find_pattern(FILE *file, const unsigned char *pattern, size_t pattern_length, int direction) {
    long int found = -1;
    tbs_bincr_enc_code(
        long int pos = ftell(file);
        char *tmp = (char *)malloc(pattern_length);
        while (fread(tmp, 1, pattern_length, file) == pattern_length) {
            if (!memcmp(tmp, pattern, pattern_length)) {
                found = ftell(file) - pattern_length;
                break;
            }
            fseek(file, 1 - (signed)pattern_length, SEEK_CUR);
            if (!direction) {
                if (ftell(file) <= 1) {
                    break;
                }
                fseek(file, -2, SEEK_CUR);
            }
        }
        free(tmp);
        fseek(file, pos, SEEK_SET);
    );
    return found;
}

uint16_t tbs_bincr_generate_key(void *section, void *end_flag) {
    /* This function must not be encrypted, because it is required for thread-safe de/encryption. */

    // TODO: Make this function threadsafe

    int seed = tbs_bincr_generate_section_seed(section, end_flag);
    tbs_bincr_key_gen_t *key_gen = tbs_bincr_key_gen_default_impl_new();
    tbs_bincr_key_gen_seed(key_gen, seed);
    uint16_t key = tbs_bincr_key_gen_next(key_gen);
    tbs_bincr_key_gen_delete(key_gen);
    tbs_log_trace("Generated a new key (with the default key generator) for the section "
        "%p with the end flag %p. The key is 0x%04X.", section, end_flag, key);
    return key;
}

int tbs_bincr_encrypt(void *section, void *end_flag, uint16_t key, int change_access_rights) {
    unsigned char *curr;
    unsigned char *begin = (unsigned char *)section;
    unsigned char *end = (unsigned char *)end_flag;
    end += sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR);
        
    tbs_log_trace("Encrypt the section %p with the end flag at %p with the key 0x%04X. Change access rights during encryption: %d",
        section, end_flag, key, change_access_rights
    );
        
    /* Invalid section. It must contain the head an the foot. */
    if ((unsigned)(end - begin) < (sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR) + sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR))) {
        tbs_log_warn("Invalid section size (too small). Section %p, end flag: %p", section, end_flag);
        return -1;
    }
        
    /* Calculate the plain data / code length. */
    uint16_t length = end - begin - (sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR) + sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR));
    uint16_t length_enc = length ^ key;
       
    if (change_access_rights) {
       
        /* Now we have to edit the code section. For this we need some rights. */
        tbs_encr_rwx(begin, end - begin);
    }
        
    /* Encrypt */
    begin[0] = TBS_BINCR_ENCRYPTED;
    begin[1] = (unsigned char)(key >> 8);
    begin[2] = (unsigned char)(key);
    begin[3] = (unsigned char)(length_enc >> 8);
    begin[4] = (unsigned char)(length_enc);
    for (curr = begin + sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR); curr < end; curr++) {
        *curr ^= tbs_bincr_next_key_byte(&key);
    }
    
    if (change_access_rights) {
        
        /* Reset the rights. */
        tbs_encr_rx(begin, end - begin);
    }
       
    tbs_log_trace("Encryption of the section %p with the end flag at %p with the key 0x%04X done.",
        section, end_flag, key
    );
    return 0;
}

int tbs_bincr_no_optimizations tbs_bincr_encrypt_file(FILE *file, tbs_bincr_key_gen_t *key_gen) {
    int res = 0;
    tbs_bincr_enc_code(
        int del_key_gen = 0;
        long int begin;
        long int end;
        long int pos = ftell(file);
        
        tbs_log_trace("Encrypt a file.");
        if (!key_gen) {
            key_gen = tbs_bincr_key_gen_default_impl_new();
            del_key_gen = 1;
            tbs_log_trace("No key generator was given. Use the default one.");
        }
        
        /*
         * To handle nested encrypted sections we first have to search an end
         * and then the begin mark.
         */
        while ((end = tbs_bincr_find_pattern(file, tbs_bincr_enc_foot_opcode(), sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR), 1)) != -1) {
            fseek(file, end - 1, SEEK_SET);
            tbs_log_trace("Found the end flag of a section: %lu. Search now the start.", end);
            
            /* Search the begin flag. */
            begin = tbs_bincr_find_pattern(file, tbs_bincr_enc_head_opcode(), sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR), 0);
            
            if (begin == -1) {
                tbs_log_warn("No start was found for the section %lu.", begin);
            
                /* Head not found. Go next. */
                fseek(file, end + sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR), SEEK_SET);
                continue;
            }
            tbs_log_warn("Found a complete section to encrypt. Section: %lu, end flag: %lu", begin, end);
            
            /* Go (back) to the the beginning. */
            fseek(file, begin, SEEK_SET);
            
            /* Store the section inside a buffer. */
            size_t buffer_len = end - begin + sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR);
            unsigned char *buffer = (unsigned char *)malloc(buffer_len);
            if (fread(buffer, 1, buffer_len, file) != buffer_len) {
            
                /* Fail: Could not read the full section. Something is very wrong. Stop! */
                res = -1;
                break;
            }
          
#ifdef WIN32

            /* No idea why this hack is needed, but otherwise wine crashes. Part 01/02 */
            unsigned char end_buffer[sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR)];
            fread(end_buffer, 1, sizeof(end_buffer), file);
            fseek(file, -sizeof(end_buffer), SEEK_CUR);
#endif

#ifndef TBS_LOG_DISABLE
            {
                unsigned char *str_buf = (unsigned char *)malloc(buffer_len * 3);
                tbs_log_buffer_hex_dump(buffer, str_buf, buffer_len);
                tbs_log_trace("Buffer (not encrypted): %s", str_buf);
                free(str_buf);
            }
#endif
            
            /* Encrypt it. */
            if (tbs_bincr_encrypt(buffer, buffer + buffer_len - sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR), tbs_bincr_key_gen_next(key_gen), 0) < 0) {
            
                /* Encryption error. Very wrong. Stop. */
                res = -2;
                break;
            }
            
            /* Write the encrypted content. */
            fseek(file, begin, SEEK_SET);
            fwrite(buffer, 1, buffer_len, file);
            
#ifdef WIN32

            /* No idea why this hack is needed, but otherwise wine crashes. Part 02/02 */
            fwrite(end_buffer, 1, sizeof(end_buffer), file);
            fseek(file, -sizeof(end_buffer), SEEK_CUR);
#endif

#ifndef TBS_LOG_DISABLE
            {
                unsigned char *str_buf = (unsigned char *)malloc(buffer_len * 3);
                tbs_log_buffer_hex_dump(buffer, str_buf, buffer_len);
                tbs_log_trace("Buffer (encrypted):     %s", str_buf);
                free(str_buf);
            }
#endif
            
            /* Another section encrypted. */
            res++;
        }
        
        fseek(file, pos, SEEK_SET);
        if (del_key_gen) {
            tbs_bincr_key_gen_delete(key_gen);
        }
    );
    tbs_log_trace("Encrypted %d pieces of code.", res);
    return res;
}

int tbs_bincr_no_optimizations tbs_bincr_decrypt_file(FILE *file) {

    // TODO: Make this function nice. Currently it is just ugly
    // TODO: Encrypt this function;)

    int decrypted = 0;
    tbs_bincr_enc_code(
        tbs_log_trace("Decrypt a file.");

        long int pos = ftell(file);
        fseek(file, 0, SEEK_SET);

        int c;
        while ((c = getc(file)) != EOF) {

            /* The first encryption byte has to be checked. */
            if (!TBS_BINCR_IS_ENCRYPTED(c)) {
                continue;
            }

            /* Store the current position. */
            long int begin = ftell(file) - 1;

            tbs_log_trace("Found a possible encrypted section: %ld", begin);

            /*
             * Maybe this section is encrypted, but how to check this?
             * Just decrypt the last bytes, they should be equal to the
             * end tag.
             */
            int k0 = getc(file);
            if (k0 == EOF) { break; }
            int k1 = getc(file);
            if (k1 == EOF) { break; }
            int l0 = getc(file);
            if (l0 == EOF) { break; }
            int l1 = getc(file);
            if (l1 == EOF) { break; }
            uint16_t key = k0 << 8 | k1;
            uint16_t length = l0 << 8 | l1;
            length ^= key;
            tbs_log_trace("Parsed key: %u", key);
            tbs_log_trace("Parsed length: %u", length);

            /* Calculate the position of the end flag. */
            long int end = begin + (long int)length + sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR);
            tbs_log_trace("The end flag position would be: %ld", end);

            /* Is it reachable? */
            if (fseek(file, end, SEEK_SET)) {
                tbs_log_warn("The end flag position is not reachable, so this is not an encrypted section.");

                /* Reset everything. */
                fseek(file, begin + 1, SEEK_SET);
                continue;
            }

            /* Calculate the current key byte. */
            uint16_t key_curr = key;
            uint16_t i;
            for (i = 0; i < length; i++) {
                tbs_bincr_next_key_byte(&key_curr);
            }

            /* Compare the end flag. */
            tbs_log_trace("Try to decrypt the foot.");
            int equal = 1;
            const unsigned char *foot = tbs_bincr_enc_foot_opcode();
            for (i = 0; i < sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR); i++) {
                c = getc(file);
                if (c == EOF)       { equal = 0; break; }
                c ^= tbs_bincr_next_key_byte(&key_curr);
                tbs_log_trace("The (decrypted) foot byte with the index %u is %u", i, c);
                if (c != foot[i])   { equal = 0; break; }
            }

            /* Check if the foot was correct. */
            if (!equal) {
                tbs_log_warn("The decrypted foot does not equal to the defined end flag, so this is not an encrypted section.");

                /* Reset everything. */
                fseek(file, begin + 1, SEEK_SET);
                continue;
            }

            /* Do now the decryption. */
            tbs_log_trace("The foot was decrypted without any problems, so this is probably an encrypted section. Decrypt it.");
            size_t buffer_len = sizeof(TBS_BINCR_ENC_HEAD_OPCODE_ARR) + length + sizeof(TBS_BINCR_ENC_FOOT_OPCODE_ARR);
            char *buffer = (char *)malloc(buffer_len);
            fseek(file, begin, SEEK_SET);
            if (fread(buffer, sizeof(char), buffer_len, file) != buffer_len) {
 
               /* Something failed. Reset everything. */
                fseek(file, begin + 1, SEEK_SET);
                continue;
            }

            int code = tbs_bincr_decrypt(buffer, 0);
            if (code) {
                tbs_log_warn("Decrypting the section failed. Error code: %d", code);
            } else {
                decrypted++;
                fseek(file, begin, SEEK_SET);
                fwrite(buffer, sizeof(char), buffer_len, file);
                fseek(file, begin + 1, SEEK_SET);
                tbs_log_trace("Decrypted a section. Totally decrypted now %d sections.", decrypted);
            }

        }

        fseek(file, pos, SEEK_SET);
        tbs_log_trace("Decrypted %d sections in a file.", decrypted);
    );

    return decrypted;
}

int tbs_bincr_reencrypt_file(FILE *file, tbs_bincr_key_gen_t *key_gen) {
   return tbs_bincr_reencrypt_file_seed(file, key_gen, 0); 
}

int tbs_bincr_no_optimizations tbs_bincr_reencrypt_file_seed(FILE *file, tbs_bincr_key_gen_t *key_gen, int additional_seed) {
    int encrypted = 0;
    tbs_bincr_enc_code(
        int del_key_gen = 0;
        if (!key_gen) {
            key_gen = tbs_bincr_key_gen_default_impl_new();
            del_key_gen = 1;
            tbs_log_trace("No key generator was given. Use the default one.");
        }

        tbs_log_trace("Try to reencrypt a file with the additional seed %d", additional_seed);
        int seed = additional_seed;
        seed ^= tbs_bincr_generate_file_seed(file);
        tbs_log_trace("Generated a new seed with the file seed. It is now %d", seed);
        int decrypted = tbs_bincr_decrypt_file(file);
        TBS_UTIL_USE_VAR(decrypted);
        tbs_log_trace("Decrypted %d sections.", decrypted);
        tbs_bincr_key_gen_seed(key_gen, seed);
        encrypted = tbs_bincr_encrypt_file(file, key_gen);
        tbs_log_trace("Encrypted %d sections.", encrypted);

        if (del_key_gen) {
            tbs_bincr_key_gen_delete(key_gen);
        }
    );
    return encrypted;
}

