#include "matrices_test.h"

int modulus=0;
int column=0;
int row=0;
Matrix * matrix = NULL;
Matrix * correct_matrix = NULL;
Matrix * small_matrix = NULL;
Matrix * correct_small_matrix = NULL;

void test_remove_column_and_row()
{
    given_matrix();
    given_column();
    given_row();
    given_correct_small_matrix();

    when_removing_column_and_row();

    assert_true("Matrix is Correct", equals(small_matrix,correct_matrix));

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
    correct_matrix = constructor(1,1);
    correct_matrix->numbers[0][0] = 3;
}

void when_removing_column_and_row()
{
    small_matrix = remove_column_and_row(matrix, column, row);
}

void test_inversion_mod_1()
{
    given_modulus();
    given_matrix();

    given_correct_matrix();

    when_calculating_inverse_mod();

    assert_true("Matrix is correct",equals(matrix,correct_matrix));

    destroy_matrix(correct_matrix);
    destroy_matrix(matrix);
}

void given_modulus()
{
    modulus=36;
}
void given_matrix()
{
    correct_matrix = constructor(2,2);
    correct_matrix->numbers[0][0] = 3;
    correct_matrix->numbers[0][1] = 2;
    correct_matrix->numbers[1][0] = 4;
    correct_matrix->numbers[1][1] = 7;
}

void given_correct_matrix()
{
    correct_matrix = constructor(2,2);
    correct_matrix->numbers[0][0] = 31;
    correct_matrix->numbers[0][1] = 22;
    correct_matrix->numbers[1][0] = 8;
    correct_matrix->numbers[1][1] = 3;
}

void when_calculating_inverse_mod()
{
    matrix = inversion_mod(matrix,modulus);
}