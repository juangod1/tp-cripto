#include "include/crypto_service.h"
#include <math.h>

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
        BMP_Image * throwable = hide_matrix(aux, shadows_path[i], number_of_bits, i);
        destroy_matrix(sh);
        destroy_matrix(g);
        destroy_Gmatrix(aux);
        destroyBMP(throwable);
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
    int number_of_bits = k == 2 ? 2 : 1;

    for(int i = 0; i < k; i++){
        GMatrix* matrix = recover_matrix(secret_images_paths[i], number_of_bits);
        secret_matrices[i] = conversion_to_matrix(matrix);
        destroy_Gmatrix(matrix);
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