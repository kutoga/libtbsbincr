#include <stdio.h>
#include <tbsenc.h>

static tbs_restricted_opt int my_encrypted_function(int a, int b) {
    int result = 0;
    tbs_enc({
        if (a < b) {
            result = b - a;
        } else {
            result = a - b;
        }
    }, _.thread_safe=false, _.re_enetrant=false, _.re_encrypt=false);
    return result;
}

static tbs_restricted_opt int my_encrypted_function2(int a, int b) {
    tbs_config my_special_settings = tbs_config_default(_.thread_safe=false, _.re_enetrant=false, _.re_encrypt=false);

    if (a < b) {
        return tbs_enc_exp(b - a, _.settings=&my_special_settings);
    } else {
        return tbs_enc_exp(a - b, _.settings=&my_special_settings);
    }
}

int main() {
    int b = 5;
    for (int a = 1; a < 3; ++a) {
        printf("Result 1: %d\n", my_encrypted_function(a, b));
        printf("Result 2: %d\n", my_encrypted_function2(a, b));
    }
    return 0;
}
