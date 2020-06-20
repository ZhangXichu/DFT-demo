# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <math.h>
# include "include/dft_small.h"

complex* dft_forward(double* data, uint8_t n){
    int i, j;
    complex* data_clx = (complex *)calloc(n, sizeof(complex));

    for (i = 0; i < n; i ++){
        complex c = {0, 0};
        for (j = 0; j < n; j++){
            complex exp_pol = cpx_to_trig(j, i, n);
            exp_pol = cpx_real_mult(exp_pol, data[j]);
            c = cpx_addition(c, exp_pol);
        }
        data_clx[i] = c;
        // cpx_print(c);
    }
    return data_clx;
}


complex* dft_real_forward(double* data, uint8_t n){
    int n_k, i, j;
    if (n % 2 == 0){
        n_k = n / 2;
    }else{
        n_k = (n - 1) / 2;
    }
    complex *out_vector = (complex *)calloc(n_k, sizeof(complex));

    for (i = 0; i < n_k; i++){
        complex c = {0, 0};
        for (j = 0; j < n; j++){
            complex exp_pol = cpx_to_trig(j, i, n);
            exp_pol = cpx_real_mult(exp_pol, data[j]);
            c = cpx_addition(c, exp_pol);
        }
        out_vector[i] = c;
    }
    return out_vector;
}

double* dft_real_inverse(complex* signals, uint8_t size){ // size = N / 2 + 1
    uint8_t i;
    uint8_t j;
    uint8_t N = (size - 1) * 2; // number of points in time domain
    double *data = (double *) calloc(N, sizeof(double));
    for (i = 0; i < N; i++){
        // scale
        signals[i].real = signals[i].real / (N / 2);
        signals[i].imaginary = signals[i].imaginary / (N / 2);
    }
    // exceptions
    signals[0].real = signals[0].real / 2;
    signals[size-1].real = signals[size-1].real / 2;

    for (i = 0; i < size; i++){
        for (j = 0; j < N; j++){
            data[j] = data[j] + signals[i].real * cos(2 * M_PI * i * j / N);
            data[j] = data[j] + signals[i].imaginary * sin(2 * M_PI * i * j / N);
        }
    }
    return data;

}

// TODO: matrix representation