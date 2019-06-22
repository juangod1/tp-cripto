#include "include/crypto_service.h"
#include "include/utils.h"
#include <math.h>


void hide_matrices(Matrix** matrix_vector, int amount_of_matrices, char* shadow_path, int number_of_bits, int shadow_number) {
    int rows = matrix_vector[0]->rows;
    int columns = matrix_vector[0]->columns;
    BitArray* bit_array = construct_bit_array(amount_of_matrices * rows * columns);

    for (int i = 0; i < amount_of_matrices; ++i) {
        BitArray* aux = build_bit_array_from_matrix(conversion_from_matrix(matrix_vector[i]));
        concatenate_bit_array(bit_array, aux);
    }

    BMP_Image * throwable = hide_matrix(bit_array, shadow_path, number_of_bits, shadow_number);
    destroyBMP(throwable);
}

Matrix*** recover_matrices(int k, int n, char** secret_images_paths) {
    Matrix*** matrix_vector = malloc(k * sizeof(GMatrix**));
    int number_of_bits = k == 2 ? 2 : 1;

    for(int i = 0; i < k; i++){
        BMP_Image* image = readBMP(secret_images_paths[i]);
        int counter = 0;

        int amount_of_matrices = (image->width/n) * (image->height/n);
        matrix_vector[i] = malloc(amount_of_matrices * sizeof(GMatrix*));

        BitArray* bit_array = recover_matrix(image, number_of_bits);

        for (int j = 0; j < amount_of_matrices; ++j) {
            matrix_vector[i][j] = conversion_to_matrix(build_Gmatrix_from_array(bit_array->numbers + counter, n, n));
            counter += n*n;
        }
    }

    return matrix_vector;
}

void encrypt_image(char* secret_image_path, char* watermark_image_path, char** shadows_path, int k, int n) {
    BMP_Image* secret_image = readBMP(secret_image_path);
    BMP_Image* watermark_image = readBMP(watermark_image_path);
    Matrix* s = image_to_matrix_conversion(secret_image);
    Matrix* w = image_to_matrix_conversion(watermark_image);
    int number_of_bits = k == 2 ? 2 : 1;

    Matrix* a = generate_a(k, s);
    Matrix** x_vec = generate_x_vec(n, k);
    Matrix** v_vec = generate_v_vec(x_vec, n, a);
    Matrix* ss = compute_ss(a);
    Matrix* r = generate_r(s, ss);
    int* c_vec = generate_c_vec(n);

    for (int i = 0; i < n; ++i) {
        int j = i +1; //index starts in 1
        Matrix* g = generate_G(j, r, c_vec, n, k);
        Matrix* sh = generate_sh(v_vec[i], g);
        GMatrix* aux = conversion_from_matrix(sh);
        destroy_matrix(sh);
        destroy_matrix(g);
        destroy_Gmatrix(aux);
    }

    Matrix* rw = generate_rw(w, ss);

    //todo: something with rw


    destroy_matrix(rw);
    destroyBMP(secret_image);
    destroyBMP(watermark_image);
    destroy_matrix(a);
    destroy_matrix_vec(x_vec,n);
    destroy_matrix_vec(v_vec,n);
    destroy_matrix(s);
    destroy_matrix(w);
    destroy_matrix(ss);
    destroy_matrix(r);
    free(c_vec);
}


int verify_watermark(Matrix * w, Matrix * w_calculated){
    return equals(w, w_calculated);
}

void decrypt_image(int k, int n, char** secret_images_paths, char * watermark_path, char * decryption_path) {
    Matrix ** secret_matrices = malloc(k*sizeof(Matrix*));
    Matrix*** shadows = recover_matrices(k, n, secret_images_paths);

    Matrix * keanu = generate_B(secret_matrices,k);
    Matrix * ss = compute_ss(keanu);
    Matrix ** g_vec = compute_G_vec(secret_matrices, k);
    Matrix * r = compute_R_from_G_vec(g_vec, k, n);
    BMP_Image * bmp_w = readBMP(watermark_path);
    Matrix * w = image_to_matrix_conversion(bmp_w);
    Matrix * rw = generate_rw(w, ss);
    Matrix * w_calculated = compute_w_from_SS_and_Rw(ss, rw);

    if(!verify_watermark(w, w_calculated)){
        printf("WATERMARK DOES NOT VALIDATE");
        exit(-1); //todo: frees?
    }

    Matrix * s = compute_s_from_SS_and_R(ss, r);
    uint8_t * image_data = malloc(sizeof(uint8_t)*s->rows*s->columns);

    for(int i=0; i<s->rows; i++){
        for(int j=0;j<s->columns;j++){
            *(image_data + j + i*s->columns) = (uint8_t)round(s->numbers[j][i]);
        }
    }

    createBMP(decryption_path,s->columns,s->rows,8);
    BMP_Image * out = readBMP(decryption_path);

    free(out->data);
    out->data = image_data;
    out->data_size = sizeof(uint8_t)*s->rows*s->columns;
    writeBMP(out, decryption_path);

    destroyBMP(out);
    destroyBMP(bmp_w);
    destroy_matrix(w_calculated);
    destroy_matrix(w);
    destroy_matrix(rw);
    destroy_matrix(r);
    destroy_matrix_vec(secret_matrices, k);
    destroy_matrix_vec(g_vec, k);
    destroy_matrix(keanu);
    destroy_matrix(ss);
    destroy_matrix(s);
}