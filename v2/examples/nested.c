#include <stdio.h>
#include <tbsenc.h>

static tbs_restricted_opt int my_encrypted_function(int a, int b) {
    int result = 0;
    tbs_enc({
        tbs_enc({
            if (tbs_enc_exp(a < b)) {
                result = tbs_enc_exp(b - a);
            } else {
                result = tbs_enc_exp(a - b);
            }
        });
    });
    return result;
}

int main() {
    int b = 5;
    for (int a = 1; a < 3; ++a) {
        printf("Result: %d\n", my_encrypted_function(a, b));
    }
    return 0;
}
