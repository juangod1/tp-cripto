// Source: https://github.com/nhomble/yasML

#ifndef matrices_h
#define matrices_h

#include <stdint.h>
/* current representation of a matrix in my mind  */
typedef struct Matrix{
    int rows;
    int columns;
    double **numbers;
} Matrix;

Matrix * calculate_cofactor_matrix();
Matrix * remove_column_and_row(Matrix *m, int column_index, int row_index);
Matrix *identity(int length);
Matrix *inversion(Matrix *m);
Matrix * inversion_mod(Matrix * m, int mod);
Matrix *constructor(int r, int c);
int destroy_matrix(Matrix *m);
void destroy_matrix_vec(Matrix ** mat_vec, int k);
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
void solve_linear_equations(Matrix * m);

#endif /* matrices */
