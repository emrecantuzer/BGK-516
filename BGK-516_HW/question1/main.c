#include <stdio.h>
#include <gmp.h>


void combination(mpz_t result, unsigned long n, unsigned long k) {
    mpz_t n_fact, k_fact, n_k_fact;
    mpz_inits(n_fact, k_fact, n_k_fact, NULL);


    mpz_fac_ui(n_fact, n);       // n!
    mpz_fac_ui(k_fact, k);       // k!
    mpz_fac_ui(n_k_fact, n - k); // (n - k)!

    // Kombinasyon: n! / (k! * (n - k)!)
    mpz_mul(n_k_fact, k_fact, n_k_fact); // k! * (n - k)!
    mpz_divexact(result, n_fact, n_k_fact); // n! / (k! * (n - k)!)

    mpz_clears(n_fact, k_fact, n_k_fact, NULL);
}


void binomial_probability(mpf_t result, unsigned long n, unsigned long k, mpf_t p) {
    mpz_t comb;
    mpf_t p_pow_k, q_pow_n_k, q, comb_f;


    mpz_init(comb);
    mpf_inits(p_pow_k, q_pow_n_k, q, comb_f, NULL);

    // q = 1 - p
    mpf_set_d(q, 1.0);
    mpf_sub(q, q, p);

    mpf_pow_ui(p_pow_k, p, k);
    mpf_pow_ui(q_pow_n_k, q, n - k);

    combination(comb, n, k);
    mpf_set_z(comb_f, comb);


    mpf_mul(result, comb_f, p_pow_k);
    mpf_mul(result, result, q_pow_n_k);


    mpz_clear(comb);
    mpf_clears(p_pow_k, q_pow_n_k, q, comb_f, NULL);
}

int main() {
    unsigned long n = 2000000;
    mpf_t p, P_X0, P_X1, P_geq_2, N;


    mpf_init2(p, 2048);
    mpf_init2(N, 2048);
    mpf_inits(P_X0, P_X1, P_geq_2, NULL);


    mpf_set_str(N, "1.11596e347", 10);


    mpf_set_ui(p, 1);
    mpf_div(p, p, N);


    binomial_probability(P_X0, n, 0, p);
    gmp_printf("P(X = 0): %.Ff\n", P_X0);


    binomial_probability(P_X1, n, 1, p);
    gmp_printf("P(X = 1): %.Ff\n", P_X1);


    mpf_set_d(P_geq_2, 1.0);
    mpf_sub(P_geq_2, P_geq_2, P_X0);
    mpf_sub(P_geq_2, P_geq_2, P_X1);


    gmp_printf("P(X >= 2): %.Ff\n", P_geq_2);


    mpf_clears(p, P_X0, P_X1, P_geq_2, N, NULL);

    return 0;
}
