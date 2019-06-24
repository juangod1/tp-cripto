#ifndef TP_CRIPTO_CRYPTO_SERVICE_H
#define TP_CRIPTO_CRYPTO_SERVICE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "matrices.h"
#include "azzahra.h"
#include "image_manipulation.h"
#include "steganography.h"

Matrix ** encrypt_image(Matrix * s, Matrix * w, int k, int n, Matrix ** rw_ret);
Matrix * decrypt_image(int k, int n, Matrix ** shs, Matrix * rw,Matrix ** w, char * shadow_numbers);
void encrypt_loop(char* secret_image_path, char* watermark_image_path, char** shadows_path, int k, int n);
void decrypt_loop(int k, int n, char ** secret_images_paths, char * rw_path, char * decryption_path);
void hide_shadow(Matrix** matrix_vector, int amount_of_matrices, char* shadow_path, int number_of_bits, char shadow_number);
Matrix*** recover_matrices(int k, int n, char** secret_images_paths, int * amount_p, char * shadow_numbers);

#endif //TP_CRIPTO_CRYPTO_SERVICE_H
