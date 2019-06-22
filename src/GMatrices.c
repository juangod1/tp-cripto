#include <stdio.h>
#include <stdlib.h>
#include "include/Gmatrices.h"
#include "tests/util.h"
#include "include/utils.h"
#include "include/matrices.h"

GMatrix *Gconstructor(int r, int c) {
    unsigned int i;
    GMatrix *m;
    if(r <= 0 || c <= 0){
        perror("Give me positive values for dimensions genius");
        return NULL;
    }
    m = malloc(sizeof(GMatrix));
    m->rows = r;
    m->columns = c;
    m->numbers = malloc(sizeof(uint8_t *)*c);
    for(i = 0; i < c; i++)
        m->numbers[i] = calloc(sizeof(uint8_t), r);
    return m;
}

int print_GMatrix(GMatrix *m){
    unsigned int i, j;
    if(m == NULL)
        return FAIL;
    for(i = 0; i < m->rows; i++){
        for(j = 0; j < m->columns; j++){
            printf("%d ", m->numbers[j][i]);
        }
        printf("\n");
    }
    printf("\n");
    return SUCC;
}

int equals_GMatrix(GMatrix *m1, GMatrix *m2){
    unsigned int i, j;
    if(m1 == NULL || m2 == NULL)
        return FAIL;
    if(m1->columns != m2->columns || m1->rows != m2->rows)
        return FAIL;
    for(i = 0; i < m1->columns; i++){
        for(j = 0; j < m1->rows; j++){
            if(m1->numbers[i][j] != m2->numbers[i][j])
                return FAIL;
        }
    }
    return SUCC;
}

int destroy_Gmatrix(GMatrix *m){
    unsigned int i;
    if(m == NULL)
        return FAIL;
    for(i = 0; i < m->columns; i++)
        free(m->numbers[i]);
    free(m->numbers);
    free(m);
    return SUCC;
}

GMatrix* conversion_from_matrix(Matrix* m) {
    GMatrix* result = Gconstructor(m->rows, m->columns);

    for(int i = 0; i < m->columns; i++){
        for(int j = 0; j < m->rows; j++){
            result->numbers[i][j] = (uint8_t) m->numbers[i][j];
        }
    }

    return result;
}

Matrix* conversion_to_matrix(GMatrix* m) {
    Matrix* result = constructor(m->rows, m->columns);

    for(int i = 0; i < m->columns; i++){
        for(int j = 0; j < m->rows; j++){
            result->numbers[i][j] = (double) m->numbers[i][j];
        }
    }

    return result;
}

