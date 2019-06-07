#include "include/azzahra.h"

Matrix * generate_a(int k, int n)
{
    Matrix * m = rand_matrix(n,k);
    print(m);
    printf("test\n");

    return m;
}