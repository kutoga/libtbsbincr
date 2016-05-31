#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include <tbs/bincr/core.h>

void help(const char *arg0);
void decrypt(int count, const char **files);
void encrypt(int time_seed, int count, const char **files);
void reencrypt(int time_seed, int count, const char **files);
FILE *try_fopen(const char *path, const char *mode);

int main(int argc, char **argv) {
    int encrypt_f = 0;
    int decrypt_f = 0;
    int reencrypt_f = 0;
    int time_seed_f = 0;
    int show_help_f = 0;
    int c;
    int ret = 0;

    while ((c = getopt(argc, argv, "edrth")) != -1) {
        switch (c) {
            case 'e':
                encrypt_f = 1;
                break;
            case 'd':
                decrypt_f = 1;
                break;
            case 'r':
                reencrypt_f = 1;
                break;
            case 't':
                time_seed_f = 1;
                break;
            case 'h':
                show_help_f = 1;
                break;
            default:
                break;
        }
    }
    if (show_help_f) {
        help(argv[0]);
    } else if (decrypt_f && time_seed_f) {
        fprintf(stderr, "-d and -t do not make sense together. Use -h for help.\n");
        ret = 1;
    } else if ((encrypt_f + decrypt_f + reencrypt_f) != 1) {
        fprintf(stderr, "Exactly one of the flags -e, -d or -r must be used. Use -h for help.\n");
        ret = 2;
    } else {

        /* All parameters are ok */
        int count = argc - optind;
        const char **files = (const char **)&argv[optind];

        if (decrypt_f) {
            decrypt(count, files);
        } else if (encrypt_f) {
            encrypt(time_seed_f, count, files);
        } else if (reencrypt_f) {
            reencrypt(time_seed_f, count, files);
        }
    }

    return ret;
}

void help(const char *arg0) {
    printf("libtbs-bincr: crypt-Tool\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("by Benjamin Bruno Meier\n");
    printf("\n");
    printf("Usage:\n");
    printf("%s [-e|-d|-r|-t|-h] file1 file2 file3...\n", arg0);
    printf("Available flags:\n");
    printf("-e Encrypt the given files (use the original file as seed => deterministic)\n");
    printf("-d Decrypt the given files\n");
    printf("-r Reencrypt the given files (use only the file as seed => deterministic)\n");
    printf("-t Instead of only using the original files as seed for encryption, also use the current time.\n");
    printf("   => non-deterministic\n");
    printf("-h Show this help\n");
}

void decrypt(int count, const char **files) {
    int i;
    for (i = 0; i < count; i++) {
        FILE *file = try_fopen(files[i], "rb+");
        if (!file) {
            continue;
        }
        int sections = tbs_bincr_decrypt_file(file);
        if (sections < 0) {
            fprintf(stderr, "Decryption of '%s' failed. Error code: %d\n", files[i], sections);
        } else {
            printf("Decrypted %d sections for '%s'\n", sections, files[i]);
        }
        fclose(file);
    }
}

void encrypt(int time_seed, int count, const char **files) {
    tbs_bincr_key_gen_t *key_gen = tbs_bincr_key_gen_default_impl_new();
    int i;
    for (i = 0; i < count; i++) {
        FILE *file = try_fopen(files[i], "rb+");
        if (!file) {
            continue;
        }
        int seed = tbs_bincr_generate_file_seed(file);
        if (time_seed) {
            seed ^= time(NULL);
        }
        tbs_bincr_key_gen_seed(key_gen, seed);
        printf("Use the seed %d for the encryption.\n", seed);
        int sections = tbs_bincr_encrypt_file(file, key_gen);
        if (sections < 0) {
            fprintf(stderr, "Encryption of '%s' failed. Error code: %d\n", files[i], sections);
        } else {
            printf("Encrypted %d sections for '%s'\n", sections, files[i]);
        }
        fclose(file);
    }
    tbs_bincr_key_gen_delete(key_gen);
}

void reencrypt(int time_seed, int count, const char **files) {
    tbs_bincr_key_gen_t *key_gen = tbs_bincr_key_gen_default_impl_new();
    int i;
    for (i = 0; i < count; i++) {
        FILE *file = try_fopen(files[i], "rb+");
        if (!file) {
            continue;
        }
        int seed = 0;
        if (time_seed) {
            seed ^= time(NULL);
        }
        printf("Use the seed %d for the reecnryption.\n", seed);
        int sections = tbs_bincr_reencrypt_file_seed(file, key_gen, seed);
        if (sections < 0) {
            fprintf(stderr, "Encryption of '%s' failed. Error code: %d\n", files[i], sections);
        } else {
            printf("Encrypted %d sections for '%s'\n", sections, files[i]);
        }
        fclose(file);
    }
    tbs_bincr_key_gen_delete(key_gen);
}

FILE *try_fopen(const char *path, const char *mode) {
    FILE *res = fopen(path, mode);
    if (!res) {
        fprintf(stderr, "It failed to open the file '%s'\n", path);
    }
    return res;
}

