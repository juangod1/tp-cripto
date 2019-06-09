#include "matrices_test.h"

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