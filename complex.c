#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "include/complex.h"

#define EPSILON pow(10, -6)

complex cpx_addition(complex a, complex b){
    complex c = {a.real + b.real, a.imaginary + b.imaginary};
    return c;
}

complex cpx_real_mult(complex a, double k){
    complex c = {a.real * k, a.imaginary * k};
    return c;
}

complex cpx_cpx_mult(complex a, complex b){
    double re = a.real*b.real - a.imaginary*b.imaginary;
    double im = a.real*b.imaginary + a.imaginary*b.real;
    complex c = {re, im};

    return c;
}

complex cpx_to_trig(int i, int j, int M){
    double re = cos(2 * M_PI * i * j / M);
    double im = -sin(2 * M_PI * i * j / M);

    complex c = {re, im};

    return c;
}

complex* real_to_cpx(double* data_real, uint32_t N){
    complex *res = (complex *)calloc(N, sizeof(complex));
    uint32_t i;
    for (i = 0; i < N; i++){
        complex c = {0, 0};
        c.real = data_real[i];
        res[i] = c;
    }
    return res;
}

double get_amplitude(complex c){
    double res = pow(c.imaginary, 2) + pow(c.real, 2);
    return sqrt(res);
}

double get_phase(complex c){
    double res = acos(c.real / get_amplitude(c));
    // in the third or forth octant
    if (c.real < -EPSILON){
        // phase ranges in (-pi, pi]
        return -res;
    }
    return res;

    // double res = atan2(c.imaginary, c.real);
    // return res;

}

int cpx_write(complex c, char* filename, FILE *stream){
    FILE *out_file = freopen(filename, "a", stream);
    if (out_file == NULL){
        printf("Error: cannot open file.");
        exit(-1);
    }
    fprintf(out_file, "%0.2f %0.2f %0.2f %0.2f\n", c.real, c.imaginary, get_amplitude(c), get_phase(c));
    fflush(out_file);
    return 0;
}

void cpx_print(complex c){
    printf("%0.2f +  %0.2fj   ", c.real, c.imaginary);
}
