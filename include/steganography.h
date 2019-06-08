//
// Created by Martina on 08/06/2019.
//

#ifndef TP_CRIPTO_STEGA_H
#define TP_CRIPTO_STEGA_H

#include "image_manipulation.h"
#include "matrices.h"

BMP_Image* hide_matrix(Matrix* m, char* path, int number_of_bits);
Matrix* recover_matrix(BMP_Image image, int number_of_bits);

#endif //TP_CRIPTO_STEGA_H
