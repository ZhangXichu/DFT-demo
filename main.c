# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <stdbool.h>

# include "include/dft.h"
# include "include/matrix.h"
# include "include/config.h"
# include "include/fft.h"
# include "include/simple_rng.h"

void print_cpx_vector(complex *vector, uint32_t n);
void print_real_vector(double *vector, uint32_t n);
void write_real_vector(double *vector, uint32_t n, char *filename, FILE *stream);
void write_complex_vector(complex *vector, uint32_t n, char *filename, FILE *stream);
bool complex_vec_comp(complex *v1, complex *v2, uint32_t n);


/**
 * @brief  test and output data
 * @note   
 * @retval 0 if successful, -1 otherwise
 */
int main(){

    int ret = 0;

    #ifdef TEST_TRANSFORMATION
        #ifdef TEST_DFT_COMPLEX_FORWARD
            printf("Test DFT complex forward.\n");
            // uint32_t n = 4;
            // uint32_t n = 16;
            uint32_t n = 20;  

            uint32_t i;

            // double data[4] = {1, 0 , 2, 0};
            double data[20] = {2, 3, -1, 1, 2.5, 4, 3.2, 1, 5, 6, 4.3, 9, -3, 1, 2.5, 4, 3.2, 1, 5, 6};
            complex sol[20] = {{59.7, 0}, {-6.388,0.679}, {9.112, 14.138}, {-6.445,2.952}, {17.149,6.898}, {-4.3,6}, {-7.212,6.898},{0.609,6.756},
                {-11.249,-14.138}, {5.024,3.03}, {-12.3,0},{5.024,3.03}, {-11.249,14.138}, {0.609,-6.756}, {-7.212,6.898}, {-4.3,-6},
                {17.149,-6.898}, {-6.445,-2.952}, {9.112,-14.138}, {-6.388,-0.679}};


            // double data[16] = {1}; // impulse
            // double data[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; // bit sequence 1
            // double data[16] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}; // bit sequence 2

            // uint32_t n = 21; // odd n
            // double data[21] = {2, 3, -1, 1, 2.5, 4, 3.2, 1, 5, 6, 4.3, 9, -3, 1, 2.5, 4, 3.2, 1, 5, 6, 9};

            // complex *res = dft_complex_forward(data, n);
            complex *res = dft_complex_forward(data, n);

            // output the transformed series
            char *filename = "forward_dft.txt";
            FILE *out_file = fopen(filename, "w");

            if (out_file == NULL) {
                printf("Error in opening new file.\n");
                exit(1);
            }

            for (i = 0; i < n; i++){
                cpx_print(res[i]);
                printf("\n");
                ret = cpx_write(res[i], filename, out_file);

            }
            printf("\n");

            printf("Output amplitude: \n");
            for (i = 0; i < n; i++){
                printf("%0.2f\n", get_amplitude(res[i]));
            }
            printf("\n");

            printf("Output phase: \n");
            for (i = 0; i < n; i++){
                printf("%0.2f\n", get_phase(res[i]));
            }
            printf("\n");

            printf("Output comlex numbers after transformation: \n");
            print_cpx_vector(res, n);

            complex_vec_comp(res, sol, n);

            // n = 4;
            n = 8;
            printf("Test DFT complex forward - complex.\n");
            complex c0 = {-0.81, -0.59};
            complex c1 = {0.31, 0.95};
            complex c2 = {-0.81, 0.59};
            complex c3 = {0.31, -0.95};
            complex c4 = {1.57, -5.67};
            complex c5 = {0.64,-12.04};
            complex c6 = {-0.81, 0.59};
            complex c7 = {0.31, 11.87};
            complex data_c[] = {c0, c1, c2, c3, c4, c5, c6, c7};
            complex* res_c = dft_complex_forward_c(data_c, n);
            print_cpx_vector(res_c, n);
            printf("\n");

            printf("Test DFT complex inverse - complex.\n");
            complex* res_ci = dft_complex_inverse_c(res_c, n);

            print_cpx_vector(res_ci, n);

            complex_vec_comp(res_ci, data_c, n);

            free(res);
        #endif

        #ifdef TEST_DFT_REAL_FORWARD
            // uint32_t size = 4;
            // uint32_t size = 16;
            uint32_t size = 20;

            // double data[4] = {2, 3, -1, 1};
            // double data[16] = {1}; // impulse
            double data[20] = {2, 3, -1, 1, 2.5, 4, 3.2, 1, 5, 6, 4.3, 9, -3, 1, 2.5, 4, 3.2, 1, 5, 6};
            complex sol[20] = {{59.7, 0}, {-6.388,0.679}, {9.112, 14.138}, {-6.445,2.952}, {17.149,6.898}, {-4.3,6}, {-7.212,6.898},{0.609,6.756},
                {-11.249,-14.138}, {5.024,3.03}, {-12.3,0},{5.024,3.03}, {-11.249,14.138}, {0.609,-6.756}, {-7.212,6.898}, {-4.3,-6},
                {17.149,-6.898}, {-6.445,-2.952}, {9.112,-14.138}, {-6.388,-0.679}};

            // odd length
            // uint32_t size = 21;
            // double data[21] = {2, 3, -1, 1, 2.5, 4, 3.2, 1, 5, 6, 4.3, 9, -3, 1, 2.5, 4, 3.2, 1, 5, 6, 9};

            complex *out_vector = dft_real_forward(data, size);
            print_cpx_vector(out_vector, size/2 + 1);

            complex_vec_comp(out_vector, sol, size);

            char *filename = "dft_real.txt"; // file to store the transformned data
            // erase the content in file first
            FILE* out = fopen(filename, "w");
            write_complex_vector(out_vector, size / 2 + 1, filename, out);

            free(out_vector);
        #endif

        #ifdef TEST_DFT_REAL_INVERSE
            // generate signals
            uint32_t i;
            uint32_t size = 33;
            uint32_t N = (size - 1) * 2; // (33 - 1) * 2 = 64
            complex *signals = (complex *)calloc(size, sizeof(complex));
            for (i = 0; i < size; i++){
                complex c = {0, 0};
                /* simple implse */
                  // c.real = 1;
                  // c.imaginary = 0;  

                /* init of a sigle wave */ 
                  // c.real = 0;
                  // c.imaginary = 0; 
                signals[i] = c;
            }
            signals[1].real = size - 1; // a single cosine wave

            printf("The sinusoids and cosinusoids to be synthesized: \n");
            print_cpx_vector(signals, size);
            char *filename_sig = "freq_complex_data.txt"; // file to store the transformed data
            // erase the content in file first
            FILE* out_sig = fopen(filename_sig, "w");
            write_complex_vector(signals, size, filename_sig, out_sig);

            printf("Real data sythesized (in time domain): \n");
            double *data = dft_real_inverse(signals, size);
            print_real_vector(data, N);

            char *filename = "time_real_data.txt";
            // erase the content in file first
            FILE* out_data = fopen(filename, "w");
            write_real_vector(data, N, filename, out_data);

            free(data);
        #endif

        #ifdef TEST_FFT
            uint32_t N = 16;
            double data_real[16] = {2, 3, -1, 1, 2.5, 4, 3.2, 1, 5, 6, 4.3, 9, -3, 1, 2.5, 4};
            complex *data_cpx = real_to_cpx_vector(data_real, N);

            // complex* c_arr = prep_real_fft(data_real, N);
            // N = N/2;
            
            printf("FFT: forward.\n");
            complex *data_res = fft_radix2_forward(data_cpx, N);
            print_cpx_vector(data_res, N);
            printf("\n");

            printf("FFT: inverse.\n");
            complex *data_res_i = fft_radix2_inverse(data_res, N);
            print_cpx_vector(data_res_i, N);

            free(data_res_i);

        #endif

        #ifdef TEST_FFT_PRIME
            uint32_t N = 17;
            uint32_t g = 3; // 3 is a primitive root of 17
            double data_real[17] = {2, 3, -1, 1, 2.5, 4, 3.2, 1, 5, 6, 4.3, 9, -3, 1, 2.5, 4, 1};
            complex sol[17] = {{45.5,0}, {-13.115,2.312}, {8.114,-0.656}, {0.829,13.99}, {-3.266,-8.494}, {0.957,-11.981},
                  {7.858,3.936}, {-12.003,-5.562}, {4.876,-8.973}, {4.876,8.973}, {-12.003,5.562}, {7.858,-3.936}, {0.957,11.981},
                  {-3.266,8.494}, {0.829,-13.99}, {8.114,0.656}, {-13.115,-2.312}};

            // small
            // uint32_t N = 5;
            // uint32_t g = 2; // 2 is a primitive root of 5
            // double data_real[5] = {2, 3, -1, 1, 2.5};

            complex *data_cpx = real_to_cpx_vector(data_real, N);
            printf("FFT prime input length: forward.\n");
            complex* res = fft_prime(data_cpx, N, g);
            print_cpx_vector(res, N);
            
            complex_vec_comp(res, sol, N);

            free(res);
        #endif


    #endif

    #ifdef TEST_MATRIX
        complex polar = cpx_to_trig(1, 1, 8);
        cpx_print(polar);

        printf("TEST: initialize DFT matrix.\n");
        uint32_t matrix_size = 8;
        complex **matrix = dft_matrix(matrix_size);
        
        cpx_print_matrix(matrix, matrix_size);

        printf("TEST: multiplication with vector\n");
        uint32_t matrix_size_small = 4;
        complex **matrix_small = dft_matrix(matrix_size_small);
        // transformation of real data using complex DFT
        complex d1 = {2, 0}, d2 = {3, 0}, d3 = {-1, 0}, d4 = {1, 0};
        complex *data_c = (complex *)calloc(matrix_size_small, sizeof(complex));
        data_c[0] = d1;
        data_c[1] = d2;
        data_c[2] = d3;
        data_c[3] = d4; 
        
        complex sol[4] = {{5,0}, {3,-2}, {-3,0}, {3,2}};
        complex *vector_out = (complex *)calloc(matrix_size_small, sizeof(complex)); // out-of-place transformation

        cpx_print_matrix(matrix_small, matrix_size_small);
        printf("\n");
        cpx_matrix_vector_multi(matrix_small, data_c, vector_out, matrix_size_small);

        complex_vec_comp(sol, vector_out, matrix_size_small);

        // output transformed vector
        int i;
        for (i = 0; i < matrix_size_small; i++){
            cpx_print(vector_out[i]);
        }
        printf("\n");

        // free matrix
        for (i = 0; i < matrix_size; i++){
            free(matrix[i]);
        }
        free(matrix);
        
        for (i = 0; i < matrix_size_small; i++){
            free(matrix_small[i]);
        }
        free(matrix_small);
    #endif

    // compare the speed of naive DFT and FFT, and plot
    #ifdef SPEED_DFT_FFT
    uint32_t size_exp;
    uint32_t size;
    clock_t time_start_dft, time_end_dft, time_dft, time_start_fft, time_end_fft, time_fft;

    // first run takes more time
    size = 2;
    init_rand_vector(size);
    prng(size);

    complex *res_dft = dft_complex_forward(rand_vector_real, size);
    complex *res_fft = fft_radix2_forward(rand_vector_cpx, size);
    
    free(res_dft);
    free(res_fft);
    free(rand_vector_real);

    char *filename = "dft_fft_speed.txt";
    FILE *stream = fopen(filename, "w");
    for (size_exp = 2; size_exp < 13; size_exp++){
        size = (int)pow(2, size_exp);
        init_rand_vector(size);
        prng(size);

        time_start_dft = clock();
        complex *res_dft = dft_complex_forward(rand_vector_real, size);
        time_end_dft = clock();
        time_dft = time_end_dft - time_start_dft;
        free(res_dft);

        time_start_fft = clock();
        complex *res_fft = fft_radix2_forward(rand_vector_cpx, size);
        time_end_fft = clock();
        time_fft = time_end_fft - time_start_fft;
        free(res_fft);

        size_t k = (int) pow(10, 6); // constant for converting to microsecond
        printf("size %d dft: %ld, fft: %ld\n", size, time_dft, time_fft);
        FILE *out_file = freopen(filename, "a", stream);
        fprintf(out_file, "%ld %ld\n", time_end_dft, time_fft); // format: [time_dft] [time_fft]
        
        free(rand_vector_real);
    }
    #endif
    
    return 0;
}

void print_cpx_vector(complex *vector, uint32_t n){
    uint32_t i;
    for (i = 0; i < n; i++){
        cpx_print(vector[i]);
    }
    printf("\n");
}

void print_real_vector(double *vector, uint32_t n){
    uint32_t i;
    for (i = 0; i < n; i++){
        printf("%0.2f ", vector[i]);
    }
    printf("\n");
}

void write_real_vector(double *vector, uint32_t n, char *filename, FILE *stream){
    uint32_t i;
    // change access mode 
    FILE *out_file = freopen(filename, "a", stream);

    for (i = 0; i < n; i++){
        fprintf(out_file, "%0.2f\n", vector[i]);
    }

    fflush(out_file);
}

void write_complex_vector(complex *vector, uint32_t n, char *filename, FILE *stream){
    uint32_t i;
    FILE *out_file = freopen(filename, "a", stream);

    for (i = 0; i < n; i++){
        double re = vector[i].real;
        double im = vector[i].imaginary;
        fprintf(out_file, "%0.2f %0.2f\n", re, im);
    }

    fflush(out_file);
}

bool complex_vec_comp(complex *v1, complex *v2, uint32_t n) {
    uint32_t i;
    for (i = 0; i < n; i++) {
        double re1 = v1->real;
        double re2 = v2->real;

        double im1 = v1->imaginary;
        double im2 = v2->imaginary;

        if (re1 - re2 > 0.01 || im1 - im2 > 0.01) {
            printf("Wrong result.\n");
            return false;
        }
    }
    printf("[OK]\n");
    return true;
}
