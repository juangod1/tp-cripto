#include "include/shamir.h"

int main(void) {
    int **a, **double_s, **r, **g, *c, **rw;
    int **w, **s; //me llega como parametro
    int k = 2, n = 4; //recibo como parametro
    int **v_array, **x_array, *c_array;
    int*** g_array;
    int*** sh_array;

    do {
        a = generate_a(k, n);
        double_s = generate_double_s(a);
        r = generate_r(s, double_s);
    } while(check_elements_greater_251(r) || check_elements_greater_251(double_s));

    x_array = generate_x_array(k, n);
    v_array = generate_v_array(a, x_array);
    c_array = generate_c_array(n);
    g_array = generate_g_array(r, k, n, c_array);
    sh_array = generate_sh_array(v_array, g_array); //mandar a esteganografia

    rw = generate_rw(w, double_s); //retornar
}