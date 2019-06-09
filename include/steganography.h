#ifndef TP_CRIPTO_STEGA_H
#define TP_CRIPTO_STEGA_H

#include "image_manipulation.h"
#include "matrices.h"

/*
 * Hides matrix m in shadow image found in path and writes it in image.
 * If number of bits is 1, performs lsb (4,8).
 * If number of bits is 2, performs lsb2 (2,4).
 */
BMP_Image* hide_matrix(Matrix* m, char* path, int number_of_bits, char shadow_number);
Matrix* recover_matrix(char* image, int number_of_bits);

#endif //TP_CRIPTO_STEGA_H
