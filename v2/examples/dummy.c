#include <stdio.h>
#include <tbsenc.h>

static tbs_restricted_opt int factorial(int n) {
    return tbs_enc_exp(n <= 1 ? 1 : n * (factorial(n - 1)));
}

int main() {
    const int n = 5; 
    printf("n! = %d\n", factorial(n));
    return 0;
}
