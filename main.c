//
// Created by Juan Godfrid on 2019-06-01.
//

#include "main.h"
#include "commons.h"

void main(void){
    gsl_matrix * m = gsl_matrix_calloc(5, 5);
    double a = gsl_matrix_get(m,2,3);
    print_matrix(m);
    gsl_matrix_free(m);
}

