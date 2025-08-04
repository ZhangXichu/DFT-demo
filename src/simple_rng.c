#include <stdlib.h>
#include <time.h>

#include "simple_rng.h"

complex *rand_vector_cpx = NULL;
double *rand_vector_real = NULL;

void init_rand_vector(uint32_t size){
    // allocate memory for the global rand_vector_cpx
    rand_vector_cpx = calloc(size, sizeof(complex));
    rand_vector_real = calloc(size, sizeof(double));
}

void prng(uint32_t size){
    uint32_t i;
    uint32_t M = 2;
    double real;
    complex c = {0, 0};
    for (i = 0; i < size; i++){
        srand(time(NULL));
        real = rand() % M;
        c = real_to_cpx(real);
        rand_vector_cpx[i] = c; // load into random cpx vector
        rand_vector_real[i] = real;  // load into random real vector
    }
}

void free_rand_vector(){
    free(rand_vector_cpx);
    free(rand_vector_real);
}