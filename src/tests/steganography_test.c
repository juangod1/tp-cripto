#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/random.h"
#include "../include/image_manipulation.h"
#include "../include/matrices.h"
#include "../include/steganography.h"
#include "util.h"

char* lsb_image_path = "../tests/images/lsb.BMP";
char* lsb2_image_path = "../tests/images/lsb.BMP";
char* white_image_path = "../tests/WHT.BMP";

void test_lsb(BitArray* bit_array) {
    BMP_Image* result_image = hide_matrix(bit_array, lsb_image_path, 1, 3);
    int are_equal = 1;

    for (int k = 0; (k < bit_array->size) && are_equal; ++k) {
        are_equal = result_image->data[k] == 0xfe;
    }
    assert_true("image is correct when doing lsb", are_equal);
    assert_true("image shadow number is correct when doing lsb", result_image->shadow == 3);
    destroyBMP(result_image);
}

void test_lsb2(BitArray* bit_array) {

    BMP_Image* result_image = hide_matrix(bit_array, lsb2_image_path , 2, 5);
    int are_equal = 1;

    for (int k = 0; (k < bit_array->size) && are_equal; ++k) {
        are_equal = result_image->data[k] == 0xfc;
    }
    assert_true("image is correct when doing lsb2", are_equal);
    assert_true("image shadow number is correct when doing lsb2", result_image->shadow == 5);
    destroyBMP(result_image);
}

void test_hide_matrix() {
    BitArray* bit_array = construct_bit_array(9);

    for (int i = 0; i < bit_array->size; ++i) {
        bit_array->numbers[i] = 0;
    }

    test_lsb(bit_array);

    for (int i = 0; i < bit_array->size; ++i) {
        bit_array->numbers[i] = 0;
    }

    test_lsb2(bit_array);

//  reseting
    destroy_bit_array(bit_array);
    BMP_Image* image = readBMP(white_image_path);
    writeBMP(image, lsb_image_path);
    writeBMP(image, lsb2_image_path);
    destroyBMP(image);
}

void test_recover_matrix() {
    setSeed(rand());
    BMP_Image* image_aux = readBMP(white_image_path);
    writeBMP(image_aux, lsb_image_path);
    writeBMP(image_aux, lsb2_image_path);

    BMP_Image* lsb = readBMP(lsb_image_path);
    BMP_Image* lsb2 = readBMP(lsb2_image_path);

    BitArray* bit_array = construct_bit_array(9);

    for (int i = 0; i < bit_array->size; ++i) {
        bit_array->numbers[i] = nextChar();
    }

    BMP_Image* img1 = hide_matrix(bit_array, lsb_image_path , 1, 5);
    BitArray* recovered_lsb = recover_matrix(lsb, 1);
    BMP_Image* img2 = hide_matrix(bit_array, lsb2_image_path , 2, 5);
    BitArray* recovered_lsb_2 = recover_matrix(lsb2 , 2);

    assert_true("image recovered is the same as hidden with lsb", bit_array_equals(recovered_lsb, bit_array));
    assert_true("image recovered is the same as hidden with lsb2", bit_array_equals(recovered_lsb_2, bit_array));

//  reseting
    destroy_bit_array(recovered_lsb);
    destroy_bit_array(recovered_lsb_2);
    writeBMP(image_aux, lsb_image_path);
    writeBMP(image_aux, lsb_image_path);
    destroyBMP(image_aux);
    destroyBMP(img1);
    destroyBMP(img2);
}

void test_everything() {
    BMP_Image* shadow1 = readBMP("../shares/backtofutureshare.bmp");
    BMP_Image* shadow1_copy = readBMP("../shares/backtofutureshare.bmp");
    setSeed(rand());

    BitArray* bit_array = construct_bit_array((shadow1->width/4) * (shadow1->height/4) * 4 * 3);

    for (int k = 0; k < bit_array->size; ++k) {
        bit_array->numbers[k] = nextChar();
    }

    BMP_Image* img = hide_matrix(bit_array, "../shares/backtofutureshare.bmp", 1, 5);
    BitArray * recovered_lsb = recover_matrix(shadow1, 1);

    assert_true("image recovered is the same as hidden with lsb", bit_array == recovered_lsb);

    free(recovered_lsb);
    writeBMP(shadow1_copy, "../shares/backtofutureshare.bmp");
    destroyBMP(img);
}
