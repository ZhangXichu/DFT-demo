# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>

# include "include/dft_small.h"
# include "include/matrix.h"
# include "include/config.h"

void print_cpx_vector(complex *vector, uint8_t n);
void print_real_vector(double *vector, uint8_t n);


/**
 * @brief  test and output data
 * @note   
 * @retval 0 if successful, -1 otherwise
 */
int main(){

    int ret = 0;

    #ifdef TEST_TRANSFORMATION
        #ifdef TEST_DFT_REAL_USING_COMPLEX
            // int8_t n = 4;
            int8_t n = 20;
            uint8_t i;
            // double data[4] = {2.0, 3.0, -1.0, 1.0};
            double data[20] = {2.0, 3.0, -1.0, 1.0, 2.5, 4.0, 3.2, 1.0, 5.0, 6.0, 4.3, 9.0, -3.0, 1.0, 2.5, 4.0, 3.2, 1.0, 5.0, 6.0};
            complex *res = dft_forward(data, n);

            // output the transformed series
            for (i = 0; i < n; i++){
                cpx_print(res[i]);
                printf("\n");
                // write to file
                char *filename = "forward_dft.txt";
                ret = cpx_write(res[i], filename);

            }
            printf("\n");

            // output the amplitude of each frequency component
            for (i = 0; i < n; i++){
                printf("%0.2f\n", get_amplitude(res[i]));
            }
            printf("\n");

            // output the phase of each frequency component
            for (i = 0; i < n; i++){
                printf("%0.2f\n", get_phase(res[i]));
            }

            free(res);
        #endif

        #ifdef TEST_DFT_REAL_FORWARD
            double data_sample[4] = {2, 3, -1, 1};
            uint8_t sample_size = 4;
            complex *out_vector = dft_real_forward(data_sample, sample_size);
            print_cpx_vector(out_vector, sample_size / 2);
            free(out_vector);
        #endif

        #ifdef TEST_DFT_REAL_INVERSE
            // generate signal, impulse with value 32 at index 0 In time domain
            uint8_t i;
            uint8_t size = 33;
            complex *signals = (complex *)calloc(size, sizeof(complex));
            for (i = 0; i < size; i++){
                complex c = {0, 0};
                c.real = 0;
                c.imaginary = 0;
                signals[i] = c;
            }
            signals[5].real = 5;

            print_cpx_vector(signals, size);

            double *data = dft_real_inverse(signals, size);
            print_real_vector(data, 64);

            free(data);
        #endif


    #endif

    #ifdef TEST_MATRIX
        complex polar = cpx_to_trig(1, 1, 8);
        cpx_print(polar);

        printf("TEST: initialize DFT matrix.\n");
        uint8_t matrix_size = 8;
        complex **matrix = dft_matrix(matrix_size);
        
        cpx_print_matrix(matrix, matrix_size);

        printf("TEST: multiplication with vector\n");
        uint8_t matrix_size_small = 4;
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

void print_cpx_vector(complex *vector, uint8_t n){
    uint8_t i;
    for (i = 0; i < n; i++){
        cpx_print(vector[i]);
    }
    printf("\n");
}

void print_real_vector(double *vector, uint8_t n){
    uint8_t i;
    for (i = 0; i < n; i++){
        printf("%0.2f ", vector[i]);
    }
    printf("\n");
}

void write_real_vector(double *vector, uint8_t n){
    uint8_t i;
}