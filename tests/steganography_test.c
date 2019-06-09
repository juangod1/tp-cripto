#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/random.h"
#include "../include/image_manipulation.h"
#include "../include/matrices.h"
#include "../include/steganography.h"
#include "util.h"

void test_lsb(Matrix* m) {
    BMP_Image* result_image = hide_matrix(m, "../tests/images/lsb.BMP", 1, 3);
    int are_equal = 1;

    for (int k = 0; (k < m->columns * m->rows * 8) && are_equal; ++k) {
        are_equal = result_image->data[k] == '\xfe';
    }
    assert_true("image is correct when doing lsb", are_equal);
    assert_true("image shadow number is correct when doing lsb", result_image->shadow == 3);
    destroyBMP(result_image);
}

void test_lsb2(Matrix* m) {

    BMP_Image* result_image = hide_matrix(m, "../tests/images/lsb2.BMP", 2, 5);
    int are_equal = 1;

    for (int k = 0; (k < m->columns * m->rows * 4) && are_equal; ++k) {
        are_equal = result_image->data[k] == '\xfc';
    }
    assert_true("image is correct when doing lsb2", are_equal);
    assert_true("image shadow number is correct when doing lsb2", result_image->shadow == 5);
    destroyBMP(result_image);
}

void test_hide_matrix() {
    Matrix* m1 = constructor(3, 3);
    Matrix* m2 = constructor(3, 3);

    for (int i = 0; i < m1->rows; ++i) {
        for (int j = 0; j < m1->columns; ++j) {
            m1->numbers[i][j] = 0;
            m2->numbers[i][j] = 0;
        }
    }
    test_lsb(m1);
    test_lsb2(m2);

//  reseting
    BMP_Image* image = readBMP("../tests/WHT.BMP");
    writeBMP(image, "../tests/images/lsb.BMP");
    writeBMP(image, "../tests/images/lsb2.BMP");
    destroyBMP(image);
}

