# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>

# include "include/dft.h"
# include "include/matrix.h"
# include "include/config.h"
# include "include/fft.h"

void print_cpx_vector(complex *vector, uint32_t n);
void print_real_vector(double *vector, uint32_t n);
void write_real_vector(double *vector, uint32_t n, char *filename, FILE *stream);
void write_complex_vector(complex *vector, uint32_t n, char *filename, FILE *stream);


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
            uint32_t n = 20;
            // uint32_t n = 16;

            uint32_t i;

            // double data[4] = {2.0, 3.0, -1.0, 1.0};
            double data[20] = {2, 3, -1, 1, 2.5, 4, 3.2, 1, 5, 6, 4.3, 9, -3, 1, 2.5, 4, 3.2, 1, 5, 6};
            // double data[16] = {1}; // impulse

            // double data[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; // bit sequence 1
            // double data[16] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}; // bit sequence 2

            // complex *res = dft_complex_forward(data, n);
            complex *res = dft_complex_forward(data, n);

            // output the transformed series
            char *filename = "forward_dft.txt";
            FILE *out_file = fopen(filename, "w");
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

            free(res);
        #endif

        #ifdef TEST_DFT_REAL_FORWARD
            // uint32_t size = 4;
            uint32_t size = 16;

            // double data[4] = {2, 3, -1, 1};
            double data[16] = {1}; // impulse

            
            complex *out_vector = dft_real_forward(data, size);
            print_cpx_vector(out_vector, size / 2);

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
                // simple implse 
                // c.real = 1;
                // c.imaginary = 0;

                // init of a sigle wave
                // c.real = 0;
                // c.imaginary = 0;
                signals[i] = c;
            }
            signals[1].real = size - 1; // a single cosine wave

            printf("The sinusoids and cosinusoids to be synthesized: \n");
            print_cpx_vector(signals, size);
            char *filename_sig = "freq_complex_data.txt";
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

        #ifdef TEST_DFT_FORWARD
        uint32_t N = 16;
        double data_real[16] = {2, 3, -1, 1, 2.5, 4, 3.2, 1, 5, 6, 4.3, 9, -3, 1, 2.5, 4};
        complex *data_cpx = real_to_cpx(data_real, N);
        complex *data_res = fft_radix2(data_cpx, N);
        print_cpx_vector(data_res, N);

        free(data_res);

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
        complex *vector_out = (complex *)calloc(matrix_size_small, sizeof(complex)); // out-of-place transformation

        cpx_print_matrix(matrix_small, matrix_size_small);
        printf("\n");
        cpx_matrix_vector_multi(matrix_small, data_c, vector_out, matrix_size_small);

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
    

    return ret;
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
