#ifndef FFT_H
#define FFT_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "complex.h"

/**
 * @brief fft algorithm with radix 2
 * @note  the complex vector produced is already freed in the recursive function
 * @param  data: input random vector with complex numbers
 * @param  N: size of input data
 * @retval data after Fourier transformation
 */
complex* fft_radix2(complex* data, uint32_t N);

#endif