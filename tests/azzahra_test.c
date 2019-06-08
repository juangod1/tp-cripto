#include "azzahra_test.h"
#include <stdbool.h>
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

void given_n()
{
    n=4;
}

void given_k()
{
    k=2;
}

void when_generating_a()
{
    matrix_a = generate_a(k,n);
}

int then_a_less_than_255()
{
    for (int i=0; i<matrix_a->rows;i++)
    {
        for(int j=0; j<matrix_a->columns;j++)
        {
            int cur = matrix_a->numbers[j][i];
            if(cur>255 || cur<0)
            {
                return false;
            }
        }
    }
    return true;
}