#ifndef STL_stkconst_
#define STL_stkconst_

#include <stdio.h>
#include <stdlib.h>

const int DEBAG = 0;

const size_t INITIAL_CAPACITY  = 1;
const size_t EXPAND_MULTIPLIER = 2;

const size_t INCORRECT_SIZE = -1u;
const int    INCORRECT_DATA  = 666;

#define $ if (DEBAG)
#define STACK_ERR(stk)  StackErr (stk, __FILE__, __LINE__)
#define STACK_DUMP(stk) StackDump (stk, __FILE__, __LINE__)

struct Stack
{
    char*  CREATE_FILE;
    size_t CREATE_LINE;
    int* data;
    size_t size;
    size_t capacity;
    int err;
};

enum StackErr
{
    ERR_NOT_STACK          = 69,
    ERR_NOT_DATA           = 1,
    ERR_INCORRECT_SIZE     = 2,
    ERR_INCORRECT_CAPACITY = 4,
    ERR_NOT_MEMORY         = 8,
    ERR_ANTIOVERFLOW       = 16,
};

#endif
