#ifndef TP_CRIPTO_STEGA_H
#define TP_CRIPTO_STEGA_H

#include "image_manipulation.h"
#include "matrices.h"

/*
 * Hides matrix m in shadow image found in path.
 * If number of bits is 1, performs lsb (4,8).
 * If number of bits is 2, performs lsb2 (2,4).
 * Path to write is the path of the image that will be created.
 */
BMP_Image* hide_matrix(Matrix* m, char* path, char* path_to_write, int number_of_bits, char shadow_number);
Matrix* recover_matrix(BMP_Image image, int number_of_bits);

#endif //TP_CRIPTO_STEGA_H
