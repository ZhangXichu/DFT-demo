# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <math.h>
# include "dft.h"

complex* dft_complex_forward(double* data, uint32_t n){
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

// refactor these two functions
// takes complex input data
complex* dft_complex_forward_c(complex* data, uint32_t n){
    int i, j;
    complex* res_clx = (complex *)calloc(n, sizeof(complex));

    for (i = 0; i < n; i ++){
        complex c = {0, 0};
        for (j = 0; j < n; j++){
            complex exp_pol = cpx_to_trig(j, i, n);
            exp_pol = cpx_cpx_mult(exp_pol, data[j]);

            c = cpx_addition(c, exp_pol);
        }
        res_clx[i] = c;
        // cpx_print(c);
    }
    return res_clx;
}

// takes complex input data, inverse
complex* dft_complex_inverse_c(complex* data, uint32_t n){
    int i, j;
    complex* res_clx = (complex *)calloc(n, sizeof(complex));

    for (i = 0; i < n; i ++){
        complex c = {0, 0};
        for (j = 0; j < n; j++){
            complex exp_pol = cpx_to_trig(j, i, -n);
            exp_pol = cpx_cpx_mult(exp_pol, data[j]);

            c = cpx_addition(c, exp_pol);
        }
        res_clx[i] = c;
        // cpx_print(c);
    }

    // scaling
    for (i = 0; i<n; i++){
        res_clx[i] = cpx_real_mult(res_clx[i], 1.0 / n);
    }
    return res_clx;
}


complex* dft_real_forward(double* data, uint32_t N){
    uint32_t i, j;
    uint32_t size = N / 2 + 1;
    complex *out_vector = (complex *)calloc(size, sizeof(complex));

    for (i = 0; i < size; i++){
        complex c = {0, 0};
        for (j = 0; j < N; j++){
            c.real = c.real + data[j] * cos(2 * M_PI * i * j / N);
            c.imaginary = c.imaginary - data[j] * sin(2 * M_PI * i * j / N);
        }
        out_vector[i] = c;
    }
    return out_vector;
}

double* dft_real_inverse(complex* signals, uint32_t size){ // size = N / 2 + 1
    uint32_t i;
    uint32_t j;
    uint32_t N = (size - 1) * 2; // number of points in time domain
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
