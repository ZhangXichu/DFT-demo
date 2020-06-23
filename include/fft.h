#ifndef FFT_H
#define FFT_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "complex.h"

complex* fft_radix2(complex* data, uint32_t N);

#endif