#ifndef TP_CRIPTO_STEGANOGRAPHY_H
#define TP_CRIPTO_STEGANOGRAPHY_H

#include "image_manipulation.h"
#include "Gmatrices.h"
#include <stdint.h>

/*
 * Hides matrix m in shadow image found in path and writes it in image.
 * If number of bits is 1, performs lsb (4,8).
 * If number of bits is 2, performs lsb2 (2,4).
 * If read or write fails, returns null.
 */
BMP_Image* hide_matrix(GMatrix* m, char* path, int number_of_bits, char shadow_number);
GMatrix* recover_matrix(char* image, int number_of_bits);

#endif //TP_CRIPTO_STEGANOGRAPHY_H
