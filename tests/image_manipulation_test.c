//
// Created by Juan Godfrid on 2019-06-03.
//

#include "image_manipulation_test.h"
#include <stdio.h>
#include "util.h"
#include <time.h>
#include <stdlib.h>

void test_read(){
    BMP_Image * i = readBMP("./tests/WHT.BMP");
    assert("BMP struct is not null",i!=NULL);
    assert("read data size correctly",i->data_size==86400);
    destroyBMP(i);
}

void test_write(){
    BMP_Image * i = readBMP("./tests/WHT.BMP");
    srand(time(NULL));
    int r = rand()%50;
    i->shadow = r;
    assert("returned correct value when written",writeBMP(i,"./tests/WHT.BMP")==0);
    destroyBMP(i);
    i = readBMP("./tests/WHT.BMP");
    assert("written correct random shadow value", i->shadow == r);
    destroyBMP(i);
}