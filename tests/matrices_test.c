#include <stdlib.h>
#include "matrices_test.h"
#include "../include/utils.h"
#include "../include/Gmatrices.h"
#include "../include/random.h"

int modulus=0;
int column=0;
int row=0;
Matrix * matrix = NULL;

Matrix * inverse_matrix = NULL;
Matrix * correct_inverse_matrix = NULL;

Matrix * small_matrix = NULL;
Matrix * correct_small_matrix = NULL;

Matrix * cofactor_matrix = NULL;
Matrix * correct_cofactor_matrix = NULL;

Matrix * m1;
Matrix * m2;
Matrix * result_matrix;
Matrix * correct_result_matrix;

void test_multiplication()
{
    given_m1();
    given_m2();
    given_correct_result_matrix();

    when_multiplying_matrices();

    printf("m1\n");
    print(m1);

    printf("m2\n");
    print(m2);

    printf("result_matrix = m2*m1\n");
    print(result_matrix);

    printf("correct_result_matrix\n");
    print(correct_result_matrix);


    assert_true("Correct Result Matrix ",equals(result_matrix,correct_result_matrix)==SUCC);

    destroy_matrix(m1);
    destroy_matrix(m2);
    destroy_matrix(result_matrix);
    destroy_matrix(correct_result_matrix);
}

void given_m1()
{
    m1= constructor(4,2);
    m1->numbers[0][0] = 3;
    m1->numbers[0][1] = 6;
    m1->numbers[0][2] = 2;
    m1->numbers[0][3] = 6;
    m1->numbers[1][0] = 7;
    m1->numbers[1][1] = 1;
    m1->numbers[1][2] = 5;
    m1->numbers[1][3] = 6;
}

void given_m2()
{
    m2= constructor(2,4);
    m2->numbers[0][0] = 3;
    m2->numbers[1][0] = 6;
    m2->numbers[2][0] = 2;
    m2->numbers[3][0] = 6;
    m2->numbers[0][1] = 7;
    m2->numbers[1][1] = 1;
    m2->numbers[2][1] = 5;
    m2->numbers[3][1] = 6;
}

void given_correct_result_matrix()
{
    correct_result_matrix = constructor(2,2);
    correct_result_matrix->numbers[0][0] =85;
    correct_result_matrix->numbers[0][1] =73;
    correct_result_matrix->numbers[1][0] =73;
    correct_result_matrix->numbers[1][1] =111;
}

void when_multiplying_matrices()
{
    result_matrix = multiply(m2,m1);
}

void test_matrix_of_cofactors()
{
    given_matrix();
    given_correct_cofactor_matrix();

    when_calculating_cofactor_matrix();

    printf("cofactor_matrix\n");
    print(cofactor_matrix);
    printf("correct_cofactor_matrix\n");
    print(correct_cofactor_matrix);
    assert_true("Matrix is Correct", equals(cofactor_matrix, correct_cofactor_matrix)==SUCC);

    destroy_matrix(matrix);
    destroy_matrix(correct_cofactor_matrix);
    destroy_matrix(cofactor_matrix);
}

void given_correct_cofactor_matrix()
{
    correct_cofactor_matrix = constructor(2,2);
    correct_cofactor_matrix->numbers[0][0] = 7;
    correct_cofactor_matrix->numbers[0][1] = -2;
    correct_cofactor_matrix->numbers[1][0] = -4;
    correct_cofactor_matrix->numbers[1][1] = 3;

}

void when_calculating_cofactor_matrix()
{
    cofactor_matrix = calculate_cofactor_matrix(matrix);
}

void test_remove_column_and_row()
{
    given_matrix();
    given_column();
    given_row();
    given_correct_small_matrix();

    when_removing_column_and_row();

    printf("small_matrix\n");
    print(small_matrix);
    printf("correct_small_matrix\n");
    print(correct_small_matrix);
    assert_true("Matrix is Correct", equals(small_matrix,correct_small_matrix)==SUCC);

    destroy_matrix(small_matrix);
    destroy_matrix(correct_small_matrix);
    destroy_matrix(matrix);
}

void given_row()
{
    row=1;
}
void given_column()
{
    column=1;
}
void given_correct_small_matrix()
{
    correct_small_matrix = constructor(1,1);
    correct_small_matrix->numbers[0][0] = 3;
}

void when_removing_column_and_row()
{
    small_matrix = remove_column_and_row(matrix, column, row);
}

void test_inversion_mod_1()
{
    given_modulus();
    given_matrix();
    given_correct_inverse_matrix();

    when_calculating_inverse_mod();

    printf("inverse_matrix\n");
    print(inverse_matrix);
    printf("correct_inverse_matrix\n");
    print(correct_inverse_matrix);
    assert_true("Matrix is correct",equals(inverse_matrix,correct_inverse_matrix)==SUCC);

    destroy_matrix(inverse_matrix);
    destroy_matrix(correct_inverse_matrix);
    destroy_matrix(matrix);
}

void given_modulus()
{
    modulus=36;
}
void given_matrix()
{
    matrix = constructor(2,2);
    matrix->numbers[0][0] = 3;
    matrix->numbers[0][1] = 2;
    matrix->numbers[1][0] = 4;
    matrix->numbers[1][1] = 7;
}

void given_correct_inverse_matrix()
{
    correct_inverse_matrix = constructor(2,2);
    correct_inverse_matrix->numbers[0][0] = 31;
    correct_inverse_matrix->numbers[0][1] = 22;
    correct_inverse_matrix->numbers[1][0] = 8;
    correct_inverse_matrix->numbers[1][1] = 3;
}

void when_calculating_inverse_mod()
{
    inverse_matrix = inversion_mod(matrix,modulus);
}

void test_conversion() {
    setSeed(rand());
    GMatrix * m = Gconstructor(3, 3);
    Matrix * m_aux = constructor(3, 3);

    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
             uint8_t number = nextChar();
             m->numbers[i][j] = number;
             m_aux->numbers[i][j] = number;
        }
    }

    Matrix* matrix1 = conversion_to_matrix(m);
    assert_true("conversion to matrix is correct", equals(m_aux, matrix1));

    GMatrix* matrix2 = conversion_from_matrix(m_aux);
    assert_true("conversion to matrix is correct", equals_GMatrix(m, matrix2));

    destroy_Gmatrix(m);
    destroy_Gmatrix(matrix2);
    destroy_matrix(m_aux);
    destroy_matrix(matrix1);
}