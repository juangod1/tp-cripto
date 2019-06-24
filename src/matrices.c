#include<math.h>
#include<stdlib.h>
#include"include/matrices.h"
#include "tests/util.h"
#include "include/utils.h"
#include<stdio.h>
#include<err.h>
#include<time.h>
#include "include/random.h"

/*
* a matrix is
		columns
	pointer   .   .   .   .
rows	  |
	  |
	  V
	  .
	  .
	  .

the matrix is an array of array pointers where each array pointer corresponds to a vector
*/

#define CONST_P 251

static int row_scalar_multiply(Matrix *m, int row, double factor);
static double vector_multiply(double *col, double *row, int length);

/* make a zero matrix of given dimensions */
Matrix *constructor(int r, int c){
    unsigned int i;
    Matrix *m;
    if(r <= 0 || c <= 0){
        perror("Give me positive values for dimensions genius");
        return NULL;
    }
    m = malloc(sizeof(Matrix));
    m->rows = r;
    m->columns = c;
    m->numbers = malloc(sizeof(double *)*c);
    for(i = 0; i < c; i++)
        m->numbers[i] = calloc(sizeof(double), r);
    return m;
}


/* free memory associated with the matrix  */
int destroy_matrix(Matrix *m){
    unsigned int i;
    if(m == NULL)
        return FAIL;
    for(i = 0; i < m->columns; i++)
        free(m->numbers[i]);
    free(m->numbers);
    free(m);
    return SUCC;
}

void destroy_matrix_vec(Matrix ** mat_vec, int k)
{
    for(int i=0; i<k;i++)
    {
        destroy_matrix(mat_vec[i]);
    }
    free(mat_vec);
}

void apply_modulus(Matrix * m, int modulus){
    unsigned int i, j;
    if(m == NULL)
        return;
    for(i = 0; i < m->rows; i++){
        for(j = 0; j < m->columns; j++){
            m->numbers[j][i]=my_mod(m->numbers[j][i],modulus);
        }
    }
}

Matrix * calculate_cofactor_matrix(Matrix * m)
{
    if(m == NULL)
        return NULL;
    if(m->rows!=m->columns)
        return NULL;
    Matrix * ret = constructor(m->rows,m->columns);

    for(int i=0; i<m->rows; i++)
    {
        for(int j=0; j<m->columns;j++)
        {
            Matrix * buf = remove_column_and_row(m,j,i);
            int diagonal = i+j;
            if(diagonal%2==1)
                ret->numbers[i][j]=-my_determinant(buf);
            else
                ret->numbers[i][j]=my_determinant(buf);
            destroy_matrix(buf);
        }
    }
    return ret;
}

/* print the matrix  */
int print(Matrix *m){
    unsigned int i, j;
    if(m == NULL)
        return FAIL;
    for(i = 0; i < m->rows; i++){
        for(j = 0; j < m->columns; j++){
            printf("%f ", m->numbers[j][i]);
        }
        printf("\n");
    }
    printf("\n");
    return SUCC;
}

Matrix * remove_column_and_row(Matrix * m, int column_index, int row_index)
{
    if(m==NULL)
        return NULL;
    int size_column = m->columns-1;
    int size_row = m->rows-1;

    Matrix * ret = constructor(size_row, size_column);
    for(int i=0, i_ret=0; i<m->rows;i++)
    {
        if(i==row_index)
            continue;
        for(int j=0, j_ret=0; j<m->columns;j++)
        {
            if(j==column_index)
                continue;
            ret->numbers[j_ret][i_ret]=m->numbers[j][i];
            j_ret++;
        }
        i_ret++;
    }
    return ret;
}

Matrix * inversion_mod(Matrix * m, int mod)
{
    int64_t det = my_determinant(m);
    int inv = multiplicative_inverse(det,mod);
    if(inv==-1)
        return NULL;
    Matrix * cofactor = calculate_cofactor_matrix(m);

    Matrix * ret = constructor(m->rows,m->columns);

    for(int i=0; i<m->rows; i++)
    {
        for(int j=0; j<m->columns; j++)
        {
            double product = cofactor->numbers[j][i]* inv;
            int number = my_mod(product, mod);
            ret->numbers[j][i]=number;
        }
    }
    destroy_matrix(cofactor);
    return ret;
}

int my_mod(int64_t number, int mod)
{
    int ret = number%mod;
    if(ret<0)
    {
        ret=mod+ret;
    }
    return ret;

}

static int row_scalar_multiply(Matrix *m, int row, double factor){
    int i;
    if(m == NULL)
        return FAIL;
    if(m->rows <= row)
        return FAIL;
    for(i = 0; i < m->columns; i++) {
        m->numbers[i][row] *= factor;
        m->numbers[i][row] = my_mod(m->numbers[i][row],CONST_P);
    }
    return SUCC;
}

int equals(Matrix *m1, Matrix *m2){
    unsigned int i, j;
    if(m1 == NULL || m2 == NULL)
        return FAIL;
    if(m1->columns != m2->columns || m1->rows != m2->rows)
        return FAIL;
    for(i = 0; i < m1->columns; i++){
        for(j = 0; j < m1->rows; j++){
            if(m1->numbers[i][j] != m2->numbers[i][j])
            {

                return FAIL;

            }
        }
    }
    return SUCC;
}

Matrix *clonemx(Matrix *m){
    Matrix *copy;
    unsigned int i, j;
    copy = constructor(m->rows, m->columns);
    for(i = 0; i < m->columns; i++)
        for(j = 0; j < m->rows; j++)
            copy->numbers[i][j] = m->numbers[i][j];
    return copy;
}

Matrix *transpose(Matrix *m){
    Matrix *trans;
    unsigned int i, j;
    if(m == NULL)
        return NULL;
    trans = constructor(m->columns, m->rows);
    for(i = 0; i < trans->columns; i++){
        for(j = 0; j < trans->rows; j++)
            trans->numbers[i][j] = m->numbers[j][i];
    }
    return trans;
}

/* create random matrix of integers  */
Matrix *rand_matrix(int rows, int columns){
    Matrix *m;
    unsigned int i, j;
    srand(time(NULL));
    m = constructor(rows, columns);
    for(i = 0; i < columns; i++){
        for(j = 0; j < rows; j++){
            m->numbers[i][j] = rand();
        }
    }
    return m;
}

/* m1 x m2  */
Matrix *multiply(Matrix *m1, Matrix *m2){
    Matrix *product, *trans;
    unsigned int i, j;
    if(m1 == NULL || m2 == NULL)
        return NULL;
    if(m1->columns != m2->rows)
        return NULL;
    trans = transpose(m1);
    product = constructor(m1->rows, m2->columns);
    for(i = 0; i < product->columns; i++){
        for(j = 0; j < product->rows; j++){
            product->numbers[i][j] = vector_multiply(trans->numbers[j], m2->numbers[i], trans->rows);
        }
    }
    destroy_matrix(trans);
    return product;
}

/* v1 x v2  -- simply a helper function -- computes dot product between two vectors*/
static double vector_multiply(double *col, double *row, int length){
    double sum;
    unsigned int i;
    sum = 0;
    for(i = 0; i < length; i++){
        sum += col[i] * row[i];
    }
    return sum;
}

/* m1 += m2  */
int add(Matrix *m1, Matrix *m2){
    unsigned int i, j;
    if(m1 == NULL || m2 == NULL)
        return FAIL;
    if(m1->rows != m2->rows || m1->columns != m2->columns)
        return FAIL;
    for(i = 0; i < m1->columns; i++){
        for(j = 0; j < m1->rows; j++)
            m1->numbers[i][j] += m2->numbers[i][j];
    }
    return SUCC;
}

int subtract(Matrix *m1, Matrix *m2){
    unsigned int i, j;
    if(m1 == NULL || m2 == NULL)
        return FAIL;
    if(m1->rows != m2->rows || m1->columns != m2->columns)
        return FAIL;
    for(i = 0; i < m1->columns; i++){
        for(j = 0; j < m1->rows; j++)
            m1->numbers[i][j] -= m2->numbers[i][j];
    }
    return SUCC;
}

int64_t my_determinant(Matrix * m)
{
    if(m->columns!=m->rows)
        return -1;
    if(m->columns==1){
        return (int)m->numbers[0][0];
    }
    if(m->columns==2)
    {
        double a = m->numbers[0][0] * m->numbers[1][1];
        double b = m->numbers[0][1] * m->numbers[1][0];
        return (int)(a-b);
    }
    int64_t ret =0;
    int i=0;
    for(int j=0; j<m->columns;j++)
    {
        Matrix * aux =remove_column_and_row(m,j,i);
        if(j%2==1){
            ret-= (int64_t )m->numbers[j][i]*my_determinant(aux);
        }
        else{
            ret+= (int64_t )m->numbers[j][i]*my_determinant(aux);
        }
        destroy_matrix(aux);
    }
    return ret;
}

int multiplicative_inverse(int64_t a, int m)
{
    for(int b = 0; b < m; b++)
    {
        int a_mod = my_mod(a, m);
        int b_mod = my_mod(b, m);
        int x = my_mod(a_mod * b_mod, m);
        if(x == 1)
            return b;
    }
    return -1;
}


void substract_rows(Matrix * m, int row1, int row2,double factor)
{
    if(m->rows<=row1 || m->rows<=row2)
        return;

    for(int i=0; i<m->columns;i++)
    {
        m->numbers[i][row1]-=factor*m->numbers[i][row2];
    }
}


void solve_linear_equations(Matrix * m)
{
    if(m->rows+1!=m->columns)
        return;
    for(int i=0; i<m->rows;i++)
    {
        double pivot = m->numbers[i][i];
        double factor = multiplicative_inverse(pivot,CONST_P);
        row_scalar_multiply(m,i,factor);
        for(int j=i+1; j<m->rows;j++)
        {
            double number = m->numbers[i][j];
            substract_rows(m,j,i,number);
        }
    }

    for(int i=0; i<m->rows; i++)
    {
        int index = m->rows-i-1;
        for(int j=i+1;j<m->rows;j++)
        {
            int index2 = m->rows-1-j;
            double number = m->numbers[index][index2];
            substract_rows(m,index2,index,number);
        }
    }

    for(int i=0; i<m->rows;i++)
    {
        for(int j=0; j<m->columns;j++)
        {
            m->numbers[j][i] = my_mod(m->numbers[j][i],CONST_P);
        }
    }

}

void swap(Matrix* m, int row1, int row2, int col)
{
    for (int i = 0; i < col; i++)
    {
        double temp = m->numbers[i][row1];
        m->numbers[i][row1] = m->numbers[i][row2];
        m->numbers[i][row2] = temp;
    }
}

int compute_rank(Matrix* matrix) {
    int rank = matrix->columns;

    Matrix* m = clonemx(matrix);

    for (int row = 0; row < rank; ++row) {

        if(m->numbers[row][row]) {
            for (int col = 0; col < matrix->rows; ++col) {
                if(col != row) {
                    double mult = m->numbers[row][col] * multiplicative_inverse(m->numbers[row][row], 251);
                    for (int i = 0; i < rank; ++i) {
                        double elem = m->numbers[i][col] - mult * m->numbers[i][row];
                        m->numbers[i][col] = my_mod(elem, 251);
                    }
                }
            }
        } else {
            int reduce = 1;
            for (int i = row + 1; i < matrix->rows; ++i) {

                if(m->numbers[row][i]) {
                    swap(m, row, i, rank);
                    reduce = 0;
                    break;
                }
            }
            if(reduce) {
                rank--;
                for (int i = 0; i < matrix->rows; ++i) {
                    m->numbers[row][i] = m->numbers[rank][i];
                }
            }
            row--;
        }
    }

    destroy_matrix(m);
    return rank;
}
