#ifndef TP_CRIPTO_GMATRICES_H
#define TP_CRIPTO_GMATRICES_H


#include <stdint.h>

typedef struct GMatrix{
    int rows;
    int columns;
    uint8_t **numbers;
} GMatrix;


GMatrix *Gconstructor(int r, int c);
int printGMatrix(GMatrix *m);
int equalsGMatrix(GMatrix *m1, GMatrix *m2);
int destroy_Gmatrix(GMatrix *m);

#endif //TP_CRIPTO_GMATRICES_H
