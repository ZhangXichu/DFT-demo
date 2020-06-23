#include "include/fft.h"

// assume N is power of 2
complex* fft_radix2(complex* data, uint32_t N){
    if (N == 1){
        return data;
    }
    uint32_t i;
    // the even part
    complex *G = (complex *)calloc(N / 2, sizeof(complex));
    // the odd part
    complex *H = (complex *)calloc(N / 2, sizeof(complex));
    for (i = 0; i < N / 2; i++){
        G[i] = data[2 * i];
        H[i] = data[2 * i + 1];
    }

    complex *G_new = fft_radix2(G, N/2);
    complex *H_new = fft_radix2(H, N/2);

    complex twiggle = cpx_to_trig(1, 1, N);
    complex twiggle_new = {1, 0};

    complex *data_new = (complex *)calloc(N, sizeof(complex));
    for (i = 0; i < N / 2; i++){
        // X[j] = G'[j] + w * H'[j]
        data_new[i] = cpx_addition(G_new[i], cpx_cpx_mult(twiggle_new, H_new[i]));
        // X[j] = G'[j] - w * H'[j]
        data_new[i + N/2] = cpx_addition(G_new[i], cpx_real_mult(cpx_cpx_mult(twiggle_new, H_new[i]), -1));
        twiggle_new = cpx_cpx_mult(twiggle_new, twiggle);
    }

    free(G_new);
    free(H_new);
    free(data);

    return data_new;
}