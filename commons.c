//
// Created by Juan Godfrid on 2019-06-01.
//

#include <gsl/gsl_matrix.h>
#include "commons.h"


void print_matrix(gsl_matrix * m){
    for(int i=0 ; i < m->size1 ; i++){
        for(int j=0 ; j < m->size2 ; j++){
            printf("%d  ", (int)gsl_matrix_get(m,i,j));
        }
        putchar('\n');
    }
}