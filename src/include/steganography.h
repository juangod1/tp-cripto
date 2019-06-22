#ifndef TP_CRIPTO_STEGANOGRAPHY_H
#define TP_CRIPTO_STEGANOGRAPHY_H

#include "image_manipulation.h"
#include "utils.h"
#include <stdint.h>

BMP_Image* hide_matrix(BitArray * bit_array, char* path, int number_of_bits, char shadow_number);
BitArray * recover_matrix(BMP_Image* image, int number_of_bits);

#endif //TP_CRIPTO_STEGANOGRAPHY_H
