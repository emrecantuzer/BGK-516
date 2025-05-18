#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>


int prime_mark(mpz_t num) {
    if (mpz_cmp_ui(num, 2) < 0) return 0;
    if (mpz_cmp_ui(num, 2) == 0 || mpz_cmp_ui(num, 3) == 0) return 1;
    if (mpz_divisible_ui_p(num, 2) || mpz_divisible_ui_p(num, 3)) return 0;

    mpz_t i, sqrt_num;
    mpz_init(i);
    mpz_init(sqrt_num);
    mpz_sqrt(sqrt_num, num);

    for (mpz_set_ui(i, 5); mpz_cmp(i, sqrt_num) <= 0; mpz_add_ui(i, i, 6)) {
        if (mpz_divisible_p(num, i) || mpz_divisible_ui_p(num, mpz_get_ui(i) + 2)) {
            mpz_clear(i);
            mpz_clear(sqrt_num);
            return 0;
        }
    }
    mpz_clear(i);
    mpz_clear(sqrt_num);
    return 1;
}


void prime_observe(mpz_t n, mpz_t* primes, int* count) {
        int limit = mpz_get_ui(n);
        int* prime_mark = malloc((limit + 1) * sizeof(int));
        *count = 0;


        for (int i = 2; i <= limit; i++) {
            prime_mark[i] = 1;
        }


        for (int i = 2; i * i <= limit; i++) {
            if (prime_mark[i]) {
                for (int j = i * i; j <= limit; j += i) {
                    prime_mark[j] = 0;
                }
            }
        }


        for (int i = 2; i <= limit; i++) {
            if (prime_mark[i]) {
                mpz_init_set_ui(primes[*count], i);
                (*count)++;
            }
        }

        free(prime_mark);
    }


int prime_check_from_list(mpz_t m, mpz_t* primes, int count) {
    for (int i = 0; i < count; i++) {

        if (mpz_divisible_p(m, primes[i])) {
            return mpz_cmp(m, primes[i]) == 0 ? 1 : 0;
        }
    }
    return 1;
}


void prime_save(mpz_t* primes, int count, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Too much input for memory!!!\n");
        return;
    }

    fprintf(file, "Prime numbers to the m\n");

    for (int i = 0; i < count; i++) {
        gmp_fprintf(file, "%Zd\n", primes[i]);
    }

    fclose(file);
}

int main() {
    mpz_t n, m;
    mpz_init(n);
    mpz_init(m);
    const char *filename = "primes.csv";

    // Values
    mpz_set_ui(n, 55200);
    mpz_set_ui(m, 3515);


    mpz_t primes[129099];
    int count;
    prime_observe(n, primes, &count);


    prime_save(primes, count, filename);

    gmp_printf("Checked the List, m = %Zd is %s prime.\n", m, prime_check_from_list(m, primes, count) ? "" : "not");

    for (int i = 0; i < count; i++) {
        mpz_clear(primes[i]);
    }
    mpz_clear(n);
    mpz_clear(m);

    return 0;
}