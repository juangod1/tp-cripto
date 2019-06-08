//
// Created by Juan Godfrid on 2019-06-03.
//

#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KCYN  "\x1B[36m"
#define KYEL  "\x1B[33m"

void run_test(char * testname, void (*test)()){
    printf("%sRunning %s... \n",KCYN,testname);
    test();
}

int assert_generic(char * assertion, int boolean)
{
    printf("%sAsserting %s: ",KYEL,assertion);
    if(boolean)
    {
        success();
        return true;
    }
    fail();
    return false;
}

void assert_true(char * assertion, int boolean)
{
    int success = assert_generic(assertion,boolean);
    if(success==false)
    {
        printf("Expected: true, found %s\n",boolean ? "true" : "false");
    }
}

void assert_false(char * assertion, int boolean)
{
    int success = assert_generic(assertion,!boolean);
    if(success==false)
    {
        printf("Expected: 'false', found '%s'\n",boolean ? "true" : "false");
    }
}

void assert_equal(char * assertion, void * expected, void * found)
{
    int success = assert_generic(assertion, expected==found);
    if(success==false)
    {
        printf("Expected: '%d', found '%d'\n",(int)expected, (int)found);
    }
}

void assert_not_equal(char * assertion, void * not_expected, void * found)
{
    int success = assert_generic(assertion, not_expected!=found);
    if(success==false)
    {
        printf("Expected value different from: '%d', found '%d'\n",(int)not_expected, (int)found);
    }
}

void fail(){
    printf("%sFail\n",KRED);
}

void success(){
    printf("%sSuccess\n",KGRN);
}