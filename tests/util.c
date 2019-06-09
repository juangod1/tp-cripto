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
#define RESET "\033[0m"

void run_test(char * testname, void (*test)()){
    printf("%sRunning %s... \n%s",KCYN,testname,RESET);
    test();
}

int assert_generic(char * assertion, int boolean)
{
    printf("%sAsserting %s: %s",KYEL,assertion,RESET);
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
        printf("Expected: true, found %s\n%s",boolean ? "true" : "false",RESET);
    }
}

void assert_false(char * assertion, int boolean)
{
    int success = assert_generic(assertion,!boolean);
    if(success==false)
    {
        printf("Expected: 'false', found '%s'\n%s",boolean ? "true" : "false",RESET);
    }
}

void assert_equal_int(char * assertion, int expected, int found)
{
    int success = assert_generic(assertion, expected==found);
    if(success==false)
    {
        printf("Expected: '%d', found '%d'\n%s",expected, found,RESET);
    }
}
void assert_not_equal_int(char * assertion, int not_expected, int found)
{
    int success = assert_generic(assertion, not_expected!=found);
    if(success==false)
    {
        printf("Expected value different from: '%d', found '%d'\n%s",not_expected, found,RESET);
    }
}


void assert_equal_memory(char * assertion, void * expected, void * found)
{
    int success = assert_generic(assertion, expected==found);
    if(success==false)
    {
        printf("Expected: '%p', found '%p'\n%s",expected, found,RESET);
    }
}

void assert_not_equal_memory(char * assertion, void * not_expected, void * found)
{
    int success = assert_generic(assertion, not_expected!=found);
    if(success==false)
    {
        printf("Expected value different from: '%p', found '%p'\n%s",not_expected, found,RESET);
    }
}

void fail(){
    printf("%sFail\n",KRED);
}

void success(){
    printf("%sSuccess\n%s",KGRN,RESET);
}