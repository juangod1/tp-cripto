#include "image_manipulation_test.h"
#include <stdio.h>
#include "util.h"
#include "../include/utils.h"
#include "../include/random.h"
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

void write_random(BMP_Image * b, char * path){
    int r;
    for(int i=0;i<b->data_size;i++){
        r = nextChar();
        b->data[i] = r;
    }
    writeBMP(b, path);
}

void test_create_image_from_matrices_and_create_matrices_from_image(){
    //-----------------------------------
    // create image from matrices
    //-----------------------------------
    char *path = "../tests/test_image.bmp";
    Matrix * m1 = rand_matrix(80,80);
    Matrix * m2 = rand_matrix(80,80);

    Matrix * matrices[2]= {0};
    matrices[0] = m1;
    matrices[1] = m2;

    createImageFromMatrices(matrices, path, 2, 80, 80);

    //-----------------------------------
    // create matrices from images
    //-----------------------------------
    int amount=0;
    Matrix ** matrices_out = createMatricesFromImage(path,&amount,4);

    for(int i=0;i<2;i++){
        assert_generic( "testing that matrices are equal" , equals(matrices_out[i], matrices[i]));
    }

    destroy_matrix(m1);
    destroy_matrix(m2);

    destroy_matrix_vec(matrices_out,amount);
}