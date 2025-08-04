#ifndef SIMPLE_RNG_H
#define SIMPLE_RNG_H

#include <stdint.h>
#include "complex.h"

extern complex *rand_vector_cpx;
extern double *rand_vector_real;

/**
 * @brief  allocate memory to |rand_vector_cpx|
 * @note   
 * @param  size: size of |rand_vector_cpx|
 * @retval None
 */
void init_rand_vector(uint32_t size);

/**
 * @brief  loads random values in |rand_vector_cpx|
 * @note   range of the random numbers is {0, 1}
 * @param  size: size of |rand_vector_cpx|
 * @retval None
 */
void prng(uint32_t size);

// /**
//  * @brief  free |rand_vector_cpx|
//  * @note   
//  * @retval None
//  */
void free_rand_vector();

#endif 
