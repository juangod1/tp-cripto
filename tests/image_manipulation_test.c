//
// Created by Juan Godfrid on 2019-06-03.
//

#include "image_manipulation_test.h"
#include <stdio.h>
#include "util.h"

void test_open(){
    BMP_Image * i = openBMP("../tests/WHT.BMP");
    assert("BMP struct is not null",i!=NULL);
}