//
// Created by Juan Godfrid on 2019-06-01.
//

#include "main.h"
#include "commons.h"
#include <gsl/gsl_matrix.h>

int matrix_example(){
    gsl_matrix * m = gsl_matrix_alloc(5, 5);
    print_matrix(m);
}

