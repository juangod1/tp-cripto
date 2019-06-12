#include <stdio.h>
#include <stdlib.h>
#include "include/Gmatrices.h"
#include "tests/util.h"
#include "include/utils.h"

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

int printGMatrix(GMatrix *m){
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

int equalsGMatrix(GMatrix *m1, GMatrix *m2){
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

