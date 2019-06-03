//
// Created by Juan Godfrid on 2019-06-01.
//

#include "include/main.h"
#include "include/matrices.h"
#include "tests/main_test.h"
#include <stdio.h>

int main(void){
    main_test();
}

/* Example use of matrices

    Matrix * m = rand_matrix(4,4,256);
    Matrix * c = clonemx(m);
    print(m);

    Matrix * n = inversion(m);
    print(n);

    print(multiply(c,n));
 */