#include "azzahra_test.h"
#include <stdbool.h>
Matrix * matrix_ss = NULL;
Matrix * matrix_a = NULL;
int n;
int k;

void test_generate_a()
{
    given_n();
    given_k();
    when_generating_a();
    assert_not_equal("A is not null",matrix_a,NULL);
    assert_true("A values < 255", then_a_less_than_255());

    destroy_matrix(matrix_a);
}

void test_generate_ss()
{
    given_n();
    given_k();
    given_a();
    when_generating_ss();
    assert_false("SS is not null",matrix_ss == NULL);
    assert_true("SS values < 255", then_ss_less_than_255());
    assert_true("SS row size", 4 == matrix_ss->rows);
    assert_true("SS column size", 4 == matrix_ss->columns);

    destroy_matrix(matrix_a);
    destroy_matrix(matrix_ss);
}

void given_a()
{
    matrix_a = generate_a(k,n);
}

void given_n()
{
    n=4;
}

void given_k()
{
    k=2;
}

void when_generating_ss()
{
    matrix_ss = generate_ss(matrix_a);
}

void when_generating_a()
{
    matrix_a = generate_a(k,n);
}

int then_ss_less_than_255()
{
    return  matrix_less_than_255(matrix_ss);
}

int then_a_less_than_255()
{
    return  matrix_less_than_255(matrix_a);
}

int matrix_less_than_255(Matrix * m)
{
    for (int i=0; i<m->rows;i++)
    {
        for(int j=0; j<m->columns;j++)
        {
            int cur = m->numbers[j][i];
            if(cur>255 || cur<0)
            {
                return false;
            }
        }
    }
    return true;
}