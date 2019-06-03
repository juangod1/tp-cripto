//
// Created by Juan Godfrid on 2019-06-01.
//

#include "include/main.h"
#include "include/matrices.h"
#include <stdio.h>

int main(void){
    Matrix * m = rand_matrix(4,4,256);
    Matrix * c = clonemx(m);
    print(m);
    printf("---\n");
    Matrix * n = inversion(m);
    print(n);
    printf("---\n");
    print(multiply(c,n));
}

