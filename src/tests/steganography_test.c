#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/random.h"
#include "../include/image_manipulation.h"
#include "../include/matrices.h"
#include "../include/steganography.h"
#include "util.h"
#include "../include/crypto_service.h"

char* lsb_image_path = "../tests/images/lsb.BMP";
char* lsb2_image_path = "../tests/images/lsb2.BMP";
char* white_image_path = "../tests/WHT.BMP";

int are_equal_to_char(BMP_Image* result_image, int size, uint8_t character) {
    int are_equal = 1;

    for (int k = 0; (k < size) && are_equal; ++k) {
        are_equal = result_image->data[k] == character;
    }

    return are_equal;
}

void test_lsb() {
    BMP_Image* img = readBMP(white_image_path);

    BitArray* bit_array = construct_bit_array(img->data_size / 8);

    for (int i = 0; i < bit_array->size; ++i) {
        bit_array->numbers[i] = 0;
    }

    BMP_Image* result_image = hide_matrix(bit_array, lsb_image_path, 1, 3);

    assert_true("image is correct when doing lsb", are_equal_to_char(result_image, bit_array->size, 0xfe));
    assert_true("image shadow number is correct when doing lsb", result_image->shadow == 3);

    destroyBMP(result_image);
    destroyBMP(img);
    destroy_bit_array(bit_array);
}

void test_lsb2() {

    BMP_Image* img = readBMP(white_image_path);
    BitArray* bit_array = construct_bit_array(img->data_size / 4);

    for (int i = 0; i < bit_array->size; ++i) {
        bit_array->numbers[i] = 0;
    }

    BMP_Image* result_image = hide_matrix(bit_array, lsb2_image_path , 2, 5);

    assert_true("image is correct when doing lsb2", are_equal_to_char(result_image, bit_array->size, 0xfc));
    assert_true("image shadow number is correct when doing lsb2", result_image->shadow == 5);

    destroyBMP(result_image);
    destroyBMP(img);
    destroy_bit_array(bit_array);
}

void test_hide_matrix() {
    BMP_Image* white = readBMP(white_image_path);

    for (int j = 0; j < white->data_size; ++j) {
        white->data[j] = 0xff;
    }

    writeBMP(white, white_image_path);
    writeBMP(white, lsb_image_path);
    writeBMP(white, lsb2_image_path);

    test_lsb();
    test_lsb2();

//  reseting
    writeBMP(white, white_image_path);
    writeBMP(white, lsb_image_path);
    writeBMP(white, lsb2_image_path);
    destroyBMP(white);
}

void test_lsb_recover() {
    BMP_Image* lsb = readBMP(lsb_image_path);

    BitArray* bit_array_for_lsb = construct_bit_array(lsb->data_size / 8);

    for (int i = 0; i < bit_array_for_lsb->size; ++i) {
        bit_array_for_lsb->numbers[i] = nextChar();
    }

    destroyBMP(lsb);

    BMP_Image* img = hide_matrix(bit_array_for_lsb, lsb_image_path , 1, 5);
    lsb = readBMP(lsb_image_path);
    BitArray* recovered_lsb = recover_matrix(lsb, 1);
    assert_true("image recovered is the same as hidden with lsb", bit_array_equals(recovered_lsb, bit_array_for_lsb));

    destroy_bit_array(bit_array_for_lsb);
    destroy_bit_array(recovered_lsb);
    destroyBMP(lsb);
    destroyBMP(img);
}

void test_lsb2_recover() {
    BMP_Image* lsb2 = readBMP(lsb2_image_path);
    BitArray* bit_array_for_lsb2 = construct_bit_array(lsb2->data_size / 4);

    for (int i = 0; i < bit_array_for_lsb2->size; ++i) {
        bit_array_for_lsb2->numbers[i] = nextChar();
    }

    destroyBMP(lsb2);

    BMP_Image* img = hide_matrix(bit_array_for_lsb2, lsb2_image_path , 2, 5);
    lsb2 = readBMP(lsb2_image_path);
    BitArray* recovered_lsb_2 = recover_matrix(lsb2 , 2);
    assert_true("image recovered is the same as hidden with lsb2", bit_array_equals(recovered_lsb_2, bit_array_for_lsb2));

    destroy_bit_array(bit_array_for_lsb2);
    destroy_bit_array(recovered_lsb_2);
    destroyBMP(lsb2);
    destroyBMP(img);
}

void test_recover_matrix() {
    setSeed(rand());
    BMP_Image* image_aux = readBMP(white_image_path);

    test_lsb_recover();
    test_lsb2_recover();

//  reseting
    writeBMP(image_aux, white_image_path);
    writeBMP(image_aux, lsb_image_path);
    writeBMP(image_aux, lsb_image_path);
    destroyBMP(image_aux);
}

Matrix *** recovered_shadows = NULL;

Matrix ***  given_shadows(int n, int amount)
{
    Matrix *** shadows = malloc(n* sizeof(Matrix **));

    for(int i=0; i<n; i++) {
        shadows[i]=malloc(amount* sizeof(Matrix *));
    }

    for(int i=0; i<amount;i++) {
        shadows[0][i] = constructor(4,3);
        shadows[0][i]->numbers[0][0]=1;
        shadows[0][i]->numbers[1][0]=2;
        shadows[0][i]->numbers[2][0]=3;

        shadows[0][i]->numbers[0][1]=11;
        shadows[0][i]->numbers[1][1]=22;
        shadows[0][i]->numbers[2][1]=33;

        shadows[0][i]->numbers[0][2]=11;
        shadows[0][i]->numbers[1][2]=22;
        shadows[0][i]->numbers[2][2]=33;

        shadows[0][i]->numbers[0][3]=11;
        shadows[0][i]->numbers[1][3]=22;
        shadows[0][i]->numbers[2][3]=33;

        //mat2
        shadows[1][i] = constructor(4,3);
        shadows[1][i]->numbers[0][0]=4;
        shadows[1][i]->numbers[1][0]=3;
        shadows[1][i]->numbers[2][0]=2;

        shadows[1][i]->numbers[0][1]=44;
        shadows[1][i]->numbers[1][1]=33;
        shadows[1][i]->numbers[2][1]=22;

        shadows[1][i]->numbers[0][2]=44;
        shadows[1][i]->numbers[1][2]=33;
        shadows[1][i]->numbers[2][2]=22;

        shadows[1][i]->numbers[0][3]=44;
        shadows[1][i]->numbers[1][3]=33;
        shadows[1][i]->numbers[2][3]=22;

        //mat 3
        shadows[2][i] = constructor(4,3);
        shadows[2][i]->numbers[0][0]=5;
        shadows[2][i]->numbers[1][0]=6;
        shadows[2][i]->numbers[2][0]=7;

        shadows[2][i]->numbers[0][1]=55;
        shadows[2][i]->numbers[1][1]=66;
        shadows[2][i]->numbers[2][1]=77;

        shadows[2][i]->numbers[0][2]=55;
        shadows[2][i]->numbers[1][2]=66;
        shadows[2][i]->numbers[2][2]=77;

        shadows[2][i]->numbers[0][3]=55;
        shadows[2][i]->numbers[1][3]=66;
        shadows[2][i]->numbers[2][3]=77;

        //mat 4
        shadows[3][i] = constructor(4,3);
        shadows[3][i]->numbers[0][0]=8;
        shadows[3][i]->numbers[1][0]=7;
        shadows[3][i]->numbers[2][0]=6;

        shadows[3][i]->numbers[0][1]=88;
        shadows[3][i]->numbers[1][1]=77;
        shadows[3][i]->numbers[2][1]=66;

        shadows[3][i]->numbers[0][2]=88;
        shadows[3][i]->numbers[1][2]=77;
        shadows[3][i]->numbers[2][2]=66;

        shadows[3][i]->numbers[0][3]=88;
        shadows[3][i]->numbers[1][3]=77;
        shadows[3][i]->numbers[2][3]=66;
    }

    return shadows;
}

void when_hiding_and_recovering_shadows(int n, int amount, int* amount_p, char** shadow_paths, Matrix *** shadows) {
    for(int i=0; i<n; i++) {
        hide_shadow(shadows[i],amount,shadow_paths[i],2,i);
    }
    recovered_shadows = recover_matrices(2,4,shadow_paths, amount_p);
}


void multiple_matrix_test() {
    int n = 4;
    int amount = 7700;
    int amount_p = 0;
    char** shadow_paths = malloc(n * sizeof(char *));
    shadow_paths[0] = "../tests/images/shadow1.bmp";
    shadow_paths[1] = "../tests/images/shadow2.bmp";
    shadow_paths[2] = "../tests/images/shadow3.bmp";
    shadow_paths[3] = "../tests/images/shadow4.bmp";

    Matrix*** shadows = given_shadows(n, amount);
    when_hiding_and_recovering_shadows(n, amount, &amount_p, shadow_paths, shadows);
    assert_equal_int("Recovered amount is equal to original amount ", amount, amount_p);
    int succ = 1;
    for(int i=0; i<2 && succ; i++)
    {
        for(int j=0; j<amount && succ; j++)
        {
            succ = equals(shadows[i][j],recovered_shadows[i][j])==SUCC;
            if(!succ) {
                printf("Original Matrix[%d][%d]\n", i, j);
                print(shadows[i][j]);
                printf("Found Matrix[%d][%d]\n", i, j);
                print(recovered_shadows[i][j]);
            }
        }
    }

    assert_true("Matrix's are equal ",succ);


    for(int i=0; i<n;i++)
    {
        destroy_matrix_vec(shadows[i],amount);
    }
    for(int i=0; i<2; i++)
    {
        destroy_matrix_vec(recovered_shadows[i],amount);
    }
    free(shadow_paths);
    free(shadows);
    free(recovered_shadows);

}

void test_everything() {
    BMP_Image* shadow1 = readBMP("../shares/backtofutureshare.bmp");
    BMP_Image* shadow1_copy = readBMP("../shares/backtofutureshare.bmp");
    setSeed(rand());


    BitArray* bit_array = construct_bit_array((shadow1->width/4) * (shadow1->height/4) * 4 * 3);

    for (int k = 0; k < bit_array->size; ++k) {
        bit_array->numbers[k] = nextChar();
    }

    destroyBMP(shadow1);

    BMP_Image* img = hide_matrix(bit_array, "../shares/backtofutureshare.bmp", 2, 5);
    shadow1 = readBMP("../shares/backtofutureshare.bmp");
    BitArray * recovered_lsb = recover_matrix(shadow1, 2);

    assert_true("image recovered is the same as hidden with lsb", bit_array_equals(bit_array, recovered_lsb));

    writeBMP(shadow1_copy, "../shares/backtofutureshare.bmp");

    destroy_bit_array(bit_array);
    destroy_bit_array(recovered_lsb);
    destroyBMP(img);
    destroyBMP(shadow1);
    destroyBMP(shadow1_copy);
}
