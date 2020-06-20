#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#include "complex.h"

/**
     * @brief computes the Fourier matrix
     * @note  matrix needs to be freed later
     * @param  n: number of DFT points 
     * @retval the DFT matrix
     */
complex** dft_matrix(uint8_t n);

/**
 * @brief  multiplication of DFT matrix with an array of complex data
 * @note   
 * @param  matrix: DFT matrix
 * @param  vector_in: input vector to be transformed 
 * @param  vector_out: output vector
 * @param  n: size of the input vector
 */
void cpx_matrix_vector_multi(complex** matrix, complex* vector_in, complex* vector_out, uint8_t n);

// prints the DFT matrix 
void cpx_print_matrix(complex** matrix, uint8_t n);

#endif