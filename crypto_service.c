#include "include/crypto_service.h"
#include <math.h>

void encrypt_image(char* secret_image_path, char* watermark_image_path, char** shadows_path, int k, int n) {
    BMP_Image* secret_image = readBMP(secret_image_path);
    BMP_Image* watermark_image = readBMP(watermark_image_path);
    Matrix* s = image_to_matrix_conversion(secret_image);
    Matrix* w = image_to_matrix_conversion(watermark_image);
    int number_of_bits = k == 2 ? 2 : 1;

    Matrix* a = generate_a(k, n);
    Matrix** x_vec = generate_x_vec(n, k);
    Matrix** v_vec = generate_v_vec(x_vec, n, a);
    Matrix* ss = compute_ss(a);
    Matrix* r = generate_r(s, ss);
    int* c_vec = generate_c_vec(n);

    for (int i = 0; i < n; ++i) {
        Matrix* g = generate_G(i, r, c_vec, n, k);
        Matrix* sh = generate_sh(v_vec[i], g);
        GMatrix* aux = conversion_from_matrix(sh);
        hide_matrix(aux, shadows_path[i], number_of_bits, i);
    }

    Matrix* rw = generate_rw(w, ss);

    destroy_matrix(a);
    destroy_matrix(s);
    destroy_matrix(ss);
    destroy_matrix(r);
    free(c_vec);
}


int verify_watermark(Matrix * w, Matrix * w_calculated){
    return equals(w, w_calculated);
}

void decrypt_image(int k, int n, char** secret_images_paths, char * watermark_path, char * decryption_path) {
    Matrix ** secret_matrices = malloc(k*sizeof(Matrix*));

    for(int i = 0; i < k; i++){
        BMP_Image* s = readBMP(secret_images_paths[i]);
        secret_matrices[i] = image_to_matrix_conversion(s);
        destroyBMP(s);
    }


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
        exit(-1);
    }

    Matrix * s = compute_s_from_SS_and_R(ss, r);
    BMP_Image * out = readBMP(decryption_path);


    uint8_t * image_data = malloc(sizeof(int)*s->rows*s->columns);

    for(int i=0;i<s->rows;i++){
        for(int j=0;j<s->columns;j++){
            *(image_data + j + i*s->columns) = (int)round(s->numbers[i][j]);
        }
    }

    out->data = image_data;
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