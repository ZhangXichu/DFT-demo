#include <math.h>

#include "include/fft.h"
#include "include/config.h"
#include "include/macros.h"

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


complex* prep_real_fft(double* real_data, uint32_t N){
    uint32_t i;
    uint32_t half_size = N / 2;
    complex* cpx_data = (complex *)calloc(half_size, sizeof(complex));
    for (i = 0; i < half_size; i++){
        complex c;
        c.real = real_data[i * 2]; // Re 
        c.imaginary = real_data[i * 2 + 1]; // Im
        cpx_data[i] = c;
    }
    return cpx_data;
}

// Don't use. function doesn't give correct result, need debug 
complex* real_fft_forward(double* data, uint32_t N){
    uint32_t i;
    complex* in_cpx = prep_real_fft(data, N);

    // use original radix2 fft to compute the transformation of size N / 2
    // no need to free |in_cpx|
    complex* G = fft_radix2_forward(in_cpx, N/2);

    printf("Transformation of size N/2\n");
    for (i = 0; i < N/2; i++){
        cpx_print(G[i]);
        printf("\n");
    }
    printf("\n");
    //////////

    // reconstruct the reslut of size N from |G|, this will be an complex array of size N
    complex* res_n = (complex *)calloc(N, sizeof(complex));
    printf("Res real FFT: \n");
    for (i = 0; i < N/2; i++){

        // complex B = {0.5 + 0.5 * Br(i, N/2), 0.5 * Bi(i, N/2)};
        // complex A = {0.5 + 0.5 * Ar(i, N/2), 0.5 * Ai(i, N/2)};

        // complex G_ = cpx_conjugate(G[N/2 - i]);
        // res_n[i] = cpx_addition(cpx_cpx_mult(G[i], B), cpx_cpx_mult(G_, A));

        double r1 = 0.5 * (G[i].real + G[N/2 - i].real);
        double r2 = 0.5 * cos(2 * M_PI * i / N) * (G[i].imaginary + G[N/2 - i].imaginary);
        double r3 = 0.5 * sin(2 * M_PI * i / N) * (G[i].real + G[N/2 - i].real);

        double i1 = 0.5 * (G[i].imaginary - G[N/2 - i].imaginary);
        double i2 = 0.5 * sin(2 * M_PI * i / N) * (G[i].imaginary + G[N/2 - i].imaginary);
        double i3 = 0.5 * cos(2 * M_PI * i / N) * (G[i].real + G[N/2 - i].real);

        res_n[i].real = r1 + r2 - r3;
        res_n[i].imaginary = i1 - i2 - i3;

        // the other half: k = N/2...N-1
        // X[k] = X*[N - k]
        res_n[N - i] = cpx_conjugate(res_n[i]);
    }
    printf("\n");

    free(G);

    return res_n;
}

// TODO: try the padding version
// // init sequences {bi} and {ci}
//     // find the smallest N_ such that N_ > 2N - 4 and N is a power of 2
//     uint32_t size_new = 16; // placeholder, for the case where N = 7
//     uint32_t num_zeros = size_new - N + 1;

// TODO: debug this one
// N is a prime (in the case N = 17, N - 1 is a power of two => reduce to a radix FFT)
complex *fft_prime(complex* data, uint32_t N, uint32_t g){ // g is the generator of cyclic group mod N
    uint32_t i;
    // prepare array {a_g^-i}
    complex* arr_agi = (complex *)calloc(N-1, sizeof(complex));
    for (i = 0; i < N-1; i++){
        uint32_t index = mulp_inverse((int)pow(g, i), N);
        printf("index: %d\n", index);
        arr_agi[i] = data[index]; 
    }
    // prepare array exp(-j * 2pi/N * g^i)
    complex* arr_e = (complex *)calloc(N-1, sizeof(complex));
    for (i = 0; i < N-1; i++){
        uint32_t j = (int)(pow(g, i)) % N;
        arr_e[i] = cpx_to_trig(1, j, N-1);
    }

    ///////// DEBUG //////////////
    printf("arr_agi: \n");
    print_cpx_vector2(arr_agi, N-1);
    printf("\n");
    printf("arr_e: \n");
    print_cpx_vector2(arr_e, N-1);
    printf("\n");
    /////////////////////////////


    // calculate a_0
    complex a0 = {0, 0};
    for (i = 0; i < N; i++){
        a0 = cpx_addition(a0, data[i]);
    }
    complex* res_agi = fft_radix2_forward(arr_agi, N-1);
    complex* res_e = fft_radix2_forward(arr_e, N-1);

    ///////// DEBUG //////////////
    printf("res_agi: \n");
    print_cpx_vector2(res_agi, N-1);
    printf("\n");
    printf("res_e: \n");
    print_cpx_vector2(res_e, N-1);
    printf("\n");
    /////////////////////////////

    complex* res_ae = (complex *)calloc(N-1, sizeof(complex));
    for (i = 0; i < N-1; i++){
        res_ae[i] = cpx_cpx_mult(res_agi[i], res_e[i]);
    }
    ///////// DEBUG //////////////
    printf("res_ae: \n");
    print_cpx_vector2(res_ae, N-1);
    printf("\n");
    /////////////////////////////

    // compute the DFT^-1
    complex* res = fft_radix2_inverse(res_ae, N-1);

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