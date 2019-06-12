// Source: https://github.com/nhomble/yasML

#ifndef matrices_h
#define matrices_h

#ifdef __cplusplus
extern "C" {
#endif


#define SUCC 1
#define FAIL -1

#include <stdint.h>
/* current representation of a matrix in my mind  */
typedef struct Matrix{
    int rows;
    int columns;
    double **numbers;
} Matrix;

typedef struct GMatrix{
    int rows;
    int columns;
    uint8_t **numbers;
} GMatrix;

Matrix * calculate_cofactor_matrix();
Matrix * remove_column_and_row(Matrix *m, int column_index, int row_index);
Matrix *identity(int length);
Matrix *inversion(Matrix *m);
Matrix * inversion_mod(Matrix * m, int mod);
Matrix *constructor(int r, int c);
GMatrix *Gconstructor(int r, int c);
int printGMatrix(GMatrix *m);
int equalsGMatrix(GMatrix *m1, GMatrix *m2);
int destroy_matrix(Matrix *m);
void apply_modulus(Matrix * m, int modulus);
int print(Matrix *m);
int row_swap(Matrix *m, int a, int b);
int scalar_multiply(Matrix *m, float f);
int reduce(Matrix *m, int a, int b, float factor);
int equals(Matrix *m1, Matrix *m2);
/* we shouldn`t use clone keyword because it`s extensively used in c++ */
Matrix *clonemx(Matrix *m);
Matrix *transpose(Matrix *m);
Matrix *rand_matrix(int rows, int columns);
Matrix *rand_matrix_mod(int rows, int columns, int modulo);
Matrix *multiply(Matrix *m1, Matrix *m2);
int add(Matrix *m1, Matrix *m2);
int subtract(Matrix *, Matrix *);
Matrix *gram_schmidt(Matrix *);
double *projection(Matrix *, double *, int length);
int zero_vector(Matrix *);
Matrix *orthonormal_basis(Matrix *);
double determinant(Matrix *m);
Matrix *solved_aug_matrix(Matrix *);
void manual_entry(Matrix **m);
double *eigenvalues(Matrix *m);
int multiplicative_inverse(int a, int m);
int my_mod(double number, int mod);

#endif /* matrices */
