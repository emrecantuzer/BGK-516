#include <stdio.h>
#include <gmp.h>


void extended_gcd(mpz_t gcd, mpz_t x, mpz_t y, mpz_t a, mpz_t b) {
    if (mpz_cmp_ui(b, 0) == 0) {
        mpz_set(gcd, a);
        mpz_set_ui(x, 1);
        mpz_set_ui(y, 0);
        return;
    }

    mpz_t gcd_b, x1, y1, r;
    mpz_inits(gcd_b, x1, y1, r, NULL);
    mpz_mod(r, a, b);
    extended_gcd(gcd_b, x1, y1, b, r);

    mpz_set(x, y1);          // x = y1
    mpz_tdiv_q(y, a, b);     // q = a / b
    mpz_mul(y, y, y1);       // y = q * y1
    mpz_sub(y, x1, y);       // y = x1 - q * y1
    mpz_set(gcd, gcd_b);
    mpz_clears(x1, y1, r, gcd_b, NULL);
}

int main() {
    mpz_t n, a, gcd, x, y;


    mpz_inits(n, a, gcd, x, y, NULL);


    mpz_set_str(a, "454545242087778", 10);
    mpz_set_str(n, "4520402402", 10);

    if (mpz_cmp(a, n) > 0) {
        printf("Error: Must be 0 < a < n \n");
        mpz_clears(n, a, gcd, x, y, NULL);
        return 1;
    }

    extended_gcd(gcd, x, y, a, n);


    if (mpz_cmp_ui(gcd, 1) == 0) {
        mpz_mod(x, x, n);
        if (mpz_cmp_ui(x, 0) < 0) {
            mpz_add(x, x, n);
        }
        gmp_printf("%Zd * %Zd = 1 (mod %Zd)\n", a, x,n);
    }

    else {
        printf("There is no solution.\n");
    }

    mpz_clears(n, a, gcd, x, y, NULL);
    return 0;
}