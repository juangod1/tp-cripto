#include "image_manipulation_test.h"
#include <stdio.h>
#include "util.h"
#include "../include/utils.h"
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

void test_create_image_from_matrices_and_create_matrices_from_image(){
    char *path = "../tests/test_image.bmp";
    Matrix * m1 = rand_matrix(200,100);
    Matrix * m2 = rand_matrix(200,100);
    Matrix * m3 = rand_matrix(200,100);
    Matrix * m4 = rand_matrix(200,100);

    Matrix * matrices[4]= {0};
    matrices[0] = m1;
    matrices[1] = m2;
    matrices[2] = m3;
    matrices[3] = m4;

    printf("Generated random matrices: ");
    print(m1);
    print(m2);
    print(m3);
    print(m4);

    createImageFromMatrices(matrices, path, 3, 400, 800);

    free(m1);
    free(m2);
    free(m3);
    free(m4);
}