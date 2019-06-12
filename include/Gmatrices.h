#ifndef TP_CRIPTO_GMATRICES_H
#define TP_CRIPTO_GMATRICES_H


#include <stdint.h>
#include "matrices.h"

typedef struct GMatrix{
    int rows;
    int columns;
    uint8_t **numbers;
} GMatrix;


GMatrix *Gconstructor(int r, int c);
int print_GMatrix(GMatrix *m);
int equals_GMatrix(GMatrix *m1, GMatrix *m2);
int destroy_Gmatrix(GMatrix *m);
GMatrix* conversion_from_matrix(Matrix* m);
Matrix* conversion_to_matrix(GMatrix* m);

#endif //TP_CRIPTO_GMATRICES_H
