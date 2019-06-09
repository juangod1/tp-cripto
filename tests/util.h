//
// Created by Juan Godfrid on 2019-06-03.
//

#ifndef TP_CRIPTO_UTIL_H
#define TP_CRIPTO_UTIL_H

void run_test(char * testname, void (*test)());
void fail();
void success();
int assert_generic(char * assertion, int boolean);
void assert_true(char * assertion, int boolean);
void assert_false(char * assertion, int boolean);
void assert_equal_int(char * assertion, int expected, int found);
void assert_not_equal_int(char * assertion, int not_expected, int found);
void assert_equal_memory(char * assertion, void * expected, void * found);
void assert_not_equal_memory(char * assertion, void * not_expected, void * found);
#endif //TP_CRIPTO_UTIL_H
