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
 * @brief  inverse fft, uses subroutine |fft_radix2|
 * @note   
 * @param  data: input random vector with complex numbers
 * @param  N: size of input data
 * @retval data after inverse Fourier transformation
 */
complex* fft_radix2_inverse(complex* data, uint32_t N);

/**
 * @brief  function prepares the complex input data for radix-2 DIT-FFT and
 *   converts the 2N length array of real data into length N array of complex data
 * @param  real_data: input arrya of real data
 * @param  N: length of input arrya of real data, should be a power of 2
 * @note  the return value shoule be freed sometime
 * @retval 
 */
complex* prep_real_fft(double* real_data, uint32_t N);

/**
 * @brief  use FFT to calculate real data
 * @note   the return value shoule be freed sometime
 * @param  data: input array of real data of size N
 * @param  N: size of the real data array
 * @retval fft result of |data|, size is N
 */
complex* real_fft_forward(double* data, uint32_t N);

complex *fft_prime(complex* data, uint32_t N, uint32_t g);

#endif