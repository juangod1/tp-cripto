//
// Created by Juan Godfrid on 2019-06-01.
//

#include "main.h"
#include "matrices.h"

void main(void){
    Matrix * m = constructor(4,4);
    print(m);
    destroy_matrix(m);
}

