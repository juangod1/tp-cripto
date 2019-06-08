//
// Created by Martina on 08/06/2019.
//

#include <stdlib.h>
#include "../include/image_manipulation.h"
#include "../include/matrices.h"
#include "../include/steganography.h"

void test_hide_matrix() {
    Matrix* m = constructor(3, 3);
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            m->numbers[i][j] = rand() % 251;
        }
    }

    BMP_Image* image = hide_matrix(m, "../tests/WHT.BMP", 1);

}

