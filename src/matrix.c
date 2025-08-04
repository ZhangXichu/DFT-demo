// matrix representation of complex DFT
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

complex** dft_matrix(uint32_t n) {
    printf("dft_matrix\n");
    complex** matrix = (complex **)calloc(n, sizeof(complex*));
    int i, j;
    for (i = 0; i < n; i++){
        matrix[i] = (complex *)calloc(n, sizeof(complex));
    }
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            // expoential form: exp(-j * 2 * pi * k / N), k = i * j
            matrix[i][j] = cpx_to_trig(i, j, n);
        }
    }
    return matrix;
}

void cpx_matrix_vector_multi(complex** matrix, complex* vector_in, complex* vector_out, uint32_t n){
    int i, j;
    // complex* out_vector = (complex *)calloc(n, sizeof(complex));
    for (i = 0; i < n; i++){
        complex summation = {0, 0};
        for (j = 0; j < n; j++){
            complex product = cpx_cpx_mult(matrix[i][j], vector_in[j]);
            summation = cpx_addition(summation, product);
        }
        vector_out[i] = summation;
    }
}

void cpx_print_matrix(complex** matrix, uint32_t n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            cpx_print(matrix[i][j]);
        }
        printf("\n");
    }
}