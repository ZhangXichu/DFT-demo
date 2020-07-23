#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>

typedef struct complex
{
    /* data */
    double real;
    double imaginary;
}complex;

// addition of two comple number
complex cpx_addition(complex a, complex b);

// a complex number multiplied by a real number
complex cpx_real_mult(complex a, double k);

// multiplication of two complex numbers
complex cpx_cpx_mult(complex a, complex b);

/**
 * @brief  function converts a complex expression to trigonometric form using Euler's formula
 * @note   
 * @param  i: index of input point (outer loop)
 * @param  j: index of big summation (inner loop)
 * @param  M: number of points of DFT
 * @retval polar form of complex number
 */
complex cpx_to_trig(int i, int j, int M);


/**
 * @brief  function converts a sequence of real data to a sequence of complex data
 * @note   the complex vector returned should be freed later
 * @param  data_real: sequence of real data
 * @param  N: length of input data
 * @retval sequence of complex representation of the real data, with imaginary part set to 0
 */
complex* real_to_cpx_vector(double* data_real, uint32_t N);

/**
 * @brief  function converts a real number to a complex number
 * @note   
 * @param  num_real: input real number
 * @retval complex number with real part set to |data_real| and imaginary part set to 0
 */
complex real_to_cpx(double num_real);

/**
 * @brief  function computes the complex conjuage of a given number
 * @note   
 * @param  c: a complex number
 * @retval complex conjugate of |c|
 */
complex cpx_conjugate(complex c);

// gets the amplitude of frequency
double get_amplitude(complex c);

// gets phase of frequency
double get_phase(complex c);

/**
 * @brief  appends a complex number to a file in the form of "[re] [im] [amplitude] [phase]"
 * @note   
 * @param  c: the complex number to write
 * @param  filename: 
 * @param  stream: the file handle to be reopened
 * @retval 0 if successfull, -1 otherwise
 */
int cpx_write(complex c, char* filename, FILE *stream);

void cpx_print(complex c);

#endif