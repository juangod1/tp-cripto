//
// Created by Juan Godfrid on 2019-06-03.
//

#include "main_test.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void main_test(){
    run_test("image open test",test_read);
    run_test("image write test",test_write);
    run_test("Generate 'A' matrix test",test_generate_a );
    run_test("Remove column and row test",test_remove_column_and_row);
    run_test("Cofactor Matrix Test",test_matrix_of_cofactors);
    run_test("Modular Arithmetic Inverse Test",test_inversion_mod_1);
    //run_test("Generate 'SS' matrix test",test_generate_ss);
}