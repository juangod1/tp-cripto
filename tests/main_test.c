#include "main_test.h"
#include "matrices_test.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void main_test(){
    run_test("image open test", test_read);
    run_test("image write test", test_write);
    run_test("Generate 'A' matrix test", test_generate_a );
    run_test("Hide matrix", test_hide_matrix);
    run_test("Recover matrix", test_recover_matrix);
    run_test("Remove column and row test", test_remove_column_and_row);
    run_test("Cofactor Matrix Test", test_matrix_of_cofactors);
    run_test("Modular Arithmetic Inverse Test", test_inversion_mod_1);
    run_test("Generate 'SS' matrix test", test_generate_ss);
    run_test("Test multiplication", test_multiplication);
    run_test("Test matrix conversion", test_conversion);
    run_test("Test generate r", test_generate_r);
    run_test("Test generate v_vec", test_generate_v_vec);
    run_test("Test calculate g", test_calculate_g);
    run_test("Test generate G", test_calculate_G);
    run_test("Test generate rw", test_generate_rw);
    run_test("Test generate sh", test_generate_sh);
    run_test("Test generate B", test_generate_B);
    run_test("Test compute ss", test_compute_ss);
    run_test("Test compute G_vec", test_compute_G_vec);
    run_test("test_linear_equations",test_linear_equations);
    run_test("test_compute_small_r",test_compute_small_r);
    run_test("test_compute_R",test_compute_R);
}