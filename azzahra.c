#include "include/azzahra.h"

Matrix * generate_a(int k, int n)
{
    Matrix * m = rand_matrix_mod(n,k,256);
    print(m);

    return m;
}