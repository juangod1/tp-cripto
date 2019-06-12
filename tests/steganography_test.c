#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/random.h"
#include "../include/image_manipulation.h"
#include "../include/matrices.h"
#include "../include/steganography.h"
#include "util.h"

void test_lsb(GMatrix* m) {
    BMP_Image* result_image = hide_matrix(m, "../tests/images/lsb.BMP", 1, 3);
    int are_equal = 1;

    for (int k = 0; (k < m->columns * m->rows * 8) && are_equal; ++k) {
        are_equal = result_image->data[k] == '\xfe';
    }
    assert_true("image is correct when doing lsb", are_equal);
    assert_true("image shadow number is correct when doing lsb", result_image->shadow == 3);
    destroyBMP(result_image);
}

void test_lsb2(GMatrix* m) {

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
    GMatrix* m = constructor(3, 3);

    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            m->numbers[i][j] = 0;
        }
    }
    test_lsb(m);
    test_lsb2(m);

//  reseting
    BMP_Image* image = readBMP("../tests/WHT.BMP");
    writeBMP(image, "../tests/images/lsb.BMP");
    writeBMP(image, "../tests/images/lsb2.BMP");
    destroyBMP(image);
}

void test_recover_matrix() {
    setSeed(rand());
    BMP_Image* image_aux = readBMP("../tests/WHT.BMP");
    writeBMP(image_aux, "../tests/images/lsb.BMP");
    writeBMP(image_aux, "../tests/images/lsb2.BMP");

    GMatrix * m = Gconstructor(3, 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m->numbers[i][j] = nextChar();
        }
    }

    hide_matrix(m, "../tests/images/lsb.BMP", 1, 5);
    GMatrix* recovered_lsb = recover_matrix("../tests/images/lsb.BMP", 1);
    hide_matrix(m, "../tests/images/lsb2.BMP", 2, 5);
    GMatrix* recovered_lsb_2 = recover_matrix("../tests/images/lsb2.BMP", 2);

    assert_true("image recovered is the same as hidden with lsb", equalsGMatrix(m, recovered_lsb));
    assert_true("image recovered is the same as hidden with lsb2", equalsGMatrix(m, recovered_lsb_2));

//  reseting
    writeBMP(image_aux, "../tests/images/lsb.BMP");
    writeBMP(image_aux, "../tests/images/lsb2.BMP");
    destroyBMP(image_aux);
}

