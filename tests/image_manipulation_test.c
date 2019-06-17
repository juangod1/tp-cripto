#include "image_manipulation_test.h"
#include <stdio.h>
#include "util.h"
#include <time.h>
#include <stdlib.h>
#include <assert.h>

char* white_image = "../tests/WHT.BMP";

void test_read(){
    BMP_Image * i = readBMP(white_image);
    assert_true("BMP struct is not null", i != NULL);
    assert_true("read data size correctly",i->data_size == 86400);
    destroyBMP(i);
}

void test_write(){
    BMP_Image * i = readBMP(white_image);
    srand(time(NULL));
    int r = rand() % 50;
    i->shadow = r;
    assert_true("returned correct value when written", writeBMP(i, white_image) == 0);
    destroyBMP(i);
    i = readBMP(white_image);
    assert_true("written correct random shadow value", i->shadow == r);
    destroyBMP(i);
}