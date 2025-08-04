#include <math.h>

#include "fft.h"
#include "config.h"
#include "macros.h"
# include "dft.h"

static void print_cpx_vector2(complex *vector, uint32_t n);
static int mulp_inverse(uint32_t x, uint32_t N);

// assume N is power of 2
complex* fft_radix2(complex* data, uint32_t N, int flag){
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

    complex *G_new = fft_radix2(G, N/2, flag);
    complex *H_new = fft_radix2(H, N/2, flag);

    complex twiggle = cpx_to_trig(1, 1, N * flag);
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

complex* fft_radix2_forward(complex* data, uint32_t N){
    return fft_radix2(data, N, FORWARD);
}

complex* fft_radix2_inverse(complex* data, uint32_t N){
    uint32_t i;
    complex* res_i = fft_radix2(data, N, INVERSE);
    // scaling
    for (i = 0; i < N; i++){
        res_i[i] = cpx_real_mult(res_i[i], 1.0 / N);
    }
    return res_i;
}


// N is a prime (in the case N = 17, N - 1 is a power of two => reduce to a radix FFT)
complex *fft_prime(complex* data, uint32_t N, uint32_t g){ // g is the generator of cyclic group mod N
    uint32_t i;
    // prepare array {a_g^-i}
    complex* arr_agi = (complex *)calloc(N-1, sizeof(complex));
    for (i = 1; i < N; i++){
        uint32_t index = mulp_inverse((int)pow(g, i) % N, N);

        arr_agi[i-1] = data[index]; 
    }
    // prepare array exp(-j * 2pi/N * g^i), i = 1,...,3
    complex* arr_e = (complex *)calloc(N-1, sizeof(complex));
    for (i = 1; i < N; i++){
        uint32_t j = (int)(pow(g, i)) % N;
        arr_e[i-1] = cpx_to_trig(1, j, N);
    }

    // calculate x_0
    complex x0 = {0, 0};
    for (i = 0; i < N; i++){
        x0 = cpx_addition(x0, data[i]);
    }
    complex* res_agi = fft_radix2_forward(arr_agi, N-1);
    complex* res_e = fft_radix2_forward(arr_e, N-1);

    // cyclic convolution of |res_agi| and |res_e|
    complex* res_ae = (complex *)calloc(N-1, sizeof(complex));
    for (i = 0; i < N-1; i++){
        res_ae[i] = cpx_cpx_mult(res_agi[i], res_e[i]);
    }

    // compute the DFT^-1
    complex* res_ = fft_radix2_inverse(res_ae, N-1);

    complex* res = (complex *)calloc(N, sizeof(complex));
    res[0] = x0;
    for (i = 1; i < N; i++){
        res[i] = cpx_addition(res_[i-1], data[0]);
    }

    free(res_);
    free(res_agi);
    free(res_e);
    
    return res;
}

// a naive function to compute the multiplicative inverse
// x should be coprime to N
static int mulp_inverse(uint32_t x, uint32_t N){
    int i;
    for (i = 1; i < N; i++){
        if ((int)((x * i) % N) == 1){
            return i;
        }
    }
    return -1;
}

// for debugging
static void print_cpx_vector2(complex *vector, uint32_t n){
    uint32_t i;
    for (i = 0; i < n; i++){
        cpx_print(vector[i]);
    }
    printf("\n");
}