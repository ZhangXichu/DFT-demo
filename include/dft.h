#ifndef DFT_SMALL_H
#define DFT_SMALL_H

# include "complex.h"

/**
 * @brief  forward transformation
 * @note   array returned by this function should be freed later
 * @param  data: data in time domain, real
 * @param  n number of elements of input |data|
 * @retval transformed data in frequency domain, as an array of complex numbers 
 */
complex* dft_complex_forward(double* data, uint32_t n);

/**
 * @brief  forward transformation 
 * @note   array returned by this function should be freed later
 * @param  data: data in time domain, complex 
 * @param  n: number of elements of input |data|
 * @retval transformed data in frequency domain, as an array of complex numbers 
 */
complex* dft_complex_forward_c(complex* data, uint32_t n);

complex* dft_complex_inverse_c(complex* data, uint32_t n);

/**
 * @brief  function computes real DFT transformation, results represented with complex numbers
 * @note   returned array should be freed later
 * @param  data: data in time domain
 * @param  n: number of elements of input |data|
 * @param  *out_vector: 
 * @retval transformed data represented by complex number, 
 *          real part of out_vector: amplitude of sinusoids, imaginary part of out_vector: amplitude of cosinusoids 
 */
complex* dft_real_forward(double* data, uint32_t n);

/**
 * @brief  synthesis DFT function
 * @note   returned array should be freed later
 * @param  waves: sinusoids and cosinusoids represented as complex numbers
 * @param  size: length of |waves|
 * @retval result of real inverse dft transform
 */
double* dft_real_inverse(complex* waves, uint32_t size);

#endif