#include <stdio.h>
#include <gmp.h>

void extended_gcd(mpz_t gcd, const mpz_t a, const mpz_t b) {
    if (mpz_cmp_ui(b, 0) == 0) {
        mpz_set(gcd, a);
        return;
    }
    if (mpz_cmp_ui(a, 0) == 0) {
        mpz_set(gcd, b);
        return;
    }

    mpz_t r;
    mpz_inits(r, NULL);
    mpz_mod(r, a, b);


    extended_gcd(gcd, b, r);

    mpz_clear(r);
}

int main() {
    mpz_t a, b, gcd;
    mpz_inits(a, b, gcd, NULL);

    mpz_set_str(a, "0", 10);
    mpz_set_str(b, "11", 10);

    extended_gcd(gcd, a, b);

    gmp_printf("a = %Zd\n", a);
    gmp_printf("b = %Zd\n", b);
    gmp_printf("GCD(%Zd, %Zd) = %Zd\n", a, b, gcd);

    mpz_clears(a, b, gcd, NULL);

    return 0;
}
