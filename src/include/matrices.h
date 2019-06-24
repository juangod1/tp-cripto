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
Matrix * inversion_mod(Matrix * m, int mod);
Matrix *constructor(int r, int c);
int destroy_matrix(Matrix *m);
void destroy_matrix_vec(Matrix ** mat_vec, int k);
void apply_modulus(Matrix * m, int modulus);
int print(Matrix *m);
int equals(Matrix *m1, Matrix *m2);
Matrix *clonemx(Matrix *m);
Matrix *transpose(Matrix *m);
Matrix *rand_matrix(int rows, int columns);
Matrix *multiply(Matrix *m1, Matrix *m2);
int add(Matrix *m1, Matrix *m2);
int subtract(Matrix *, Matrix *);
int multiplicative_inverse(double a, int m);
int my_mod(double number, int mod);
void solve_linear_equations(Matrix * m);
int my_determinant(Matrix * m);
int compute_rank(Matrix* matrix);
#endif /* matrices */
