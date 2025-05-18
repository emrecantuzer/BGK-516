#include <stdio.h>
#include <gmp.h>


void extended_gcd(mpz_t gcd, mpz_t x, mpz_t y, mpz_t a, mpz_t b) {
    if (mpz_cmp_ui(b, 0) == 0) {
        mpz_set(gcd, a);
        mpz_set_ui(x, 1); // x = 1
        mpz_set_ui(y, 0); // y = 0
        return;
    }
    if (mpz_cmp_ui(a, 0) == 0) {
        printf("Error: a cannot be zero.\n");
        mpz_set_ui(gcd, 0);  // gcd = 0
        mpz_set_ui(x, 0);    // x = 0
        mpz_set_ui(y, 0);    // y = 0
        return;
    }
    mpz_t x1, y1, r;
    mpz_inits(x1, y1, r, NULL);
    mpz_mod(r, a, b);

    extended_gcd(gcd, x1, y1, b, r);


    mpz_set(x, y1);          // x = y1
    mpz_tdiv_q(y, a, b);     // q = a / b
    mpz_mul(y, y, y1);       // y = q * y1
    mpz_sub(y, x1, y);       // y = x1 - q * y1

    mpz_clears(x1, y1, r, NULL);
}

int main() {
    mpz_t a, b, gcd, x, y;


    mpz_inits(a, b, gcd, x, y, NULL);

    mpz_set_str(a, "0", 10);
    mpz_set_str(b, "4552454454656456465464521356464624264", 10);



    extended_gcd(gcd, x, y, a, b);


    gmp_printf("a = %Zd\n", a);
    gmp_printf("b = %Zd\n", b);
    gmp_printf("x = %Zd\n", x);
    gmp_printf("y = %Zd\n", y);
    gmp_printf("GCD(%Zd, %Zd) = %Zd", a, b, gcd);


    mpz_clears(a, b, gcd, x, y, NULL);
    return 0;
}
