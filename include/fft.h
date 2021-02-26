#ifndef FFT_H
#define FFT_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "complex.h"

/**
 * @brief  subroutine of fft algorithm with radix 2
 * @note  the complex vector produced is already freed in the recursive function
 * @param  data: input random vector with complex numbers
 * @param  N: size of input data
 * @param flag: FORWARD or INVERSE
 * @retval data after Fourier transformation
 */
complex* fft_radix2(complex* data, uint32_t N, int flag);

/**
 * @brief  forward fft, uses subroutine |fft_radix2|
 * @note   
 * @param  data: input random vector with complex numbers
 * @param  N: size of input data
 * @retval data after forward Fourier transformation
 */
complex* fft_radix2_forward(complex* data, uint32_t N);

/**
 * @brief  
 * @note   
 * @param  data: 
 * @param  N: 
 * @param  flag: 
 * @retval None
 */
void fft_radix2_in(complex* data, uint32_t N, int flag);

void fft_radix2_forward_in(complex* data, uint32_t N);

/**
 * @brief  inverse fft, uses subroutine |fft_radix2|
 * @note   
 * @param  data: input random vector with complex numbers
 * @param  N: size of input data
 * @retval data after inverse Fourier transformation
 */
complex* fft_radix2_inverse(complex* data, uint32_t N);

complex *fft_prime(complex* data, uint32_t N, uint32_t g);

#endif