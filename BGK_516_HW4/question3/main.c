#include <gmp.h>
#include <stdio.h>

int main() {
    mpz_t mod ;
    mpz_t a2, result2, exponent2;
    mpz_t a3, result3, exponent3;
    mpz_t a5, result5, exponent5;

    mpz_init_set_ui(mod, 163921);

    mpz_init(a2);
    mpz_init(result2);
    mpz_init_set_ui(mod, 163921);
    mpz_init_set_ui(exponent2, 2);

    mpz_init(a3);
    mpz_init(result3);
    mpz_init_set_ui(exponent3, 3);

    mpz_init(a5);
    mpz_init(result5);
    mpz_init_set_ui(exponent5, 5);


    mpz_t target2;
    mpz_init_set_ui(target2, 14641);

    mpz_t target3;
    mpz_init_set_ui(target3, 75244);

    mpz_t target5;
    mpz_init_set_ui(target5, 88789);


    for (mpz_set_ui(a2, 0); mpz_cmp(a2, mod) < 0; mpz_add_ui(a2, a2, 1)) {
        mpz_powm(result2, a2, exponent2, mod);
        if (mpz_cmp(result2, target2) == 0) {
            break;
        }
    }

    for (mpz_set_ui(a3, 0); mpz_cmp(a3, mod) < 0; mpz_add_ui(a3, a3, 1)) {
        mpz_powm(result3, a3, exponent3, mod);
        if (mpz_cmp(result3, target3) == 0) {
            break;
        }
    }


    for (mpz_set_ui(a5, 0); mpz_cmp(a5, mod) < 0; mpz_add_ui(a5, a5, 1)) {
        mpz_powm(result5, a5, exponent5, mod);
        if (mpz_cmp(result5, target5) == 0) {
            break;
        }
    }

    gmp_printf(" A^2 = %Zd\n", a2);
    gmp_printf(" A^3 = %Zd\n", a3);
    gmp_printf(" A^5 = %Zd\n", a5);

    mpz_clear(mod);

    mpz_clear(a2);
    mpz_clear(result2);
    mpz_clear(exponent2);
    mpz_clear(target2);

    mpz_clear(a3);
    mpz_clear(result3);
    mpz_clear(exponent3);
    mpz_clear(target3);

    mpz_clear(a5);
    mpz_clear(result5);
    mpz_clear(exponent5);
    mpz_clear(target5);

    return 0;
}
