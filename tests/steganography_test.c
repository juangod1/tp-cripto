#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/random.h"
#include "../include/image_manipulation.h"
#include "../include/matrices.h"
#include "../include/steganography.h"
#include "util.h"

char* lsb_image_path = "./tests/images/lsb.BMP";
char* lsb2_image_path = "./tests/images/lsb.BMP";
char* white_image_path = "./tests/WHT.BMP";

void test_lsb(GMatrix* m) {
    BMP_Image* result_image = hide_matrix(m, lsb_image_path, 1, 3);
    int are_equal = 1;

    for (int k = 0; (k < m->columns * m->rows * 8) && are_equal; ++k) {
        are_equal = result_image->data[k] == 0xfe;
    }
    assert_true("image is correct when doing lsb", are_equal);
    assert_true("image shadow number is correct when doing lsb", result_image->shadow == 3);
    destroyBMP(result_image);
}

void test_lsb2(GMatrix* m) {

    BMP_Image* result_image = hide_matrix(m, lsb2_image_path , 2, 5);
    int are_equal = 1;

    for (int k = 0; (k < m->columns * m->rows * 4) && are_equal; ++k) {
        are_equal = result_image->data[k] == 0xfc;
    }
    assert_true("image is correct when doing lsb2", are_equal);
    assert_true("image shadow number is correct when doing lsb2", result_image->shadow == 5);
    destroyBMP(result_image);
}

void test_hide_matrix() {
    GMatrix* m = Gconstructor(3, 3);

    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            m->numbers[i][j] = 0;
        }
    }
    test_lsb(m);
    test_lsb2(m);

//  reseting
    destroy_Gmatrix(m);
    BMP_Image* image = readBMP(white_image_path);
    writeBMP(image, lsb_image_path );
    writeBMP(image, lsb2_image_path );
    destroyBMP(image);
}

void test_recover_matrix() {
    setSeed(rand());
    BMP_Image* image_aux = readBMP(white_image_path);
    writeBMP(image_aux, lsb_image_path );
    writeBMP(image_aux, lsb2_image_path );

    GMatrix * m = Gconstructor(3, 3);

    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            m->numbers[i][j] = nextChar();
        }
    }

    BMP_Image* img1 = hide_matrix(m, lsb_image_path , 1, 5);
    GMatrix* recovered_lsb = recover_matrix(lsb_image_path , 1);
    BMP_Image* img2 = hide_matrix(m, lsb2_image_path , 2, 5);
    GMatrix* recovered_lsb_2 = recover_matrix(lsb2_image_path , 2);

    assert_true("image recovered is the same as hidden with lsb", equals_GMatrix(m, recovered_lsb));
    assert_true("image recovered is the same as hidden with lsb2", equals_GMatrix(m, recovered_lsb_2));

//  reseting
    destroy_Gmatrix(recovered_lsb);
    destroy_Gmatrix(recovered_lsb_2);
    destroy_Gmatrix(m);
    writeBMP(image_aux, lsb_image_path);
    writeBMP(image_aux, lsb_image_path);
    destroyBMP(image_aux);
    destroyBMP(img1);
    destroyBMP(img2);
}

