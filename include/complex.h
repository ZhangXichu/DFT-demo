#ifndef COMPLEX_H
#define COMPLEX_H

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

// gets the amplitude of frequency
double get_amplitude(complex c);

// gets phase of frequency
double get_phase(complex c);

/**
 * @brief  appends a complex number to a file in the form of "[re] [im] [amplitude] [phase]"
 * @note   
 * @param  c: the complex number to write
 * @param  filename: 
 * @retval 0 if successfull, -1 otherwise
 */
int cpx_write(complex c, char* filename);

void cpx_print(complex c);

#endif