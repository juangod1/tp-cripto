
#include "../include/crypto_service.h"
#include "../include/random.h"
#include "util.h"

void test_everything_posta() {
    int k = 4, n = 8;
    Matrix* s = constructor(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            s->numbers[j][i] = my_mod(nextChar(), 251);
        }
    }

    Matrix* w = constructor(n, n);
    char* shadow_count = malloc(k * sizeof(char));
    shadow_count[0] = 0;
    shadow_count[1] = 1;
    shadow_count[2] = 2;
    shadow_count[3] = 3;
    Matrix* rw;
    Matrix** sh = encrypt_image(s, w, k, n, &rw);


    destroy_matrix(w);
    Matrix* s_result = decrypt_image(k, n, sh, rw, &w, shadow_count);

    assert_true("are equal", equals(s, s_result)==SUCC);

    destroy_matrix(s);
    destroy_matrix(w);
    free(shadow_count);
    destroy_matrix(rw);
    destroy_matrix_vec(sh,n);
    destroy_matrix(s_result);
}

