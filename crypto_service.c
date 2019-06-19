#include "include/crypto_service.h"

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

