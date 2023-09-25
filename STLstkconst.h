#ifndef STL_stkconst_
#define STL_stkconst_

#include <stdio.h>
#include <stdlib.h>

const int DEBUG = 1;
#define $ if (DEBUG)

typedef int DataType;
#define PRINT_DATA "%d"

typedef long long CanaryType;
#define PRINT_CANARY "%d"

const size_t INITIAL_CAPACITY  = 1;
const size_t EXPAND_MULTIPLIER = 2;

const size_t INCORRECT_SIZE = -1u;
const int    INCORRECT_DATA = 666;       //

#define STACK_ERR(stk)  StackErr (stk, __FILE__, __LINE__, __func__)
#define STACK_DUMP(stk) StackDump (stk, __FILE__, __LINE__, __func__)

struct Stack
{
    CanaryType leftCanary;
    const char*  CREATE_FILE;
    const size_t CREATE_LINE;
    const char*  CREATE_FUNC;
    DataType* data;
    size_t size;
    size_t capacity;
    long long err;
    long long hashStack;
    long long hashData;
    CanaryType rightCanary;
};
       /*
struct
{
    unsigned int ERR_NOT_STACK          : 1;
    unsigned int ERR_NOT_DATA           : 1;
    unsigned int ERR_INCORRECT_SIZE     : 1;
    unsigned int ERR_INCORRECT_CAPACITY : 1;
    unsigned int ERR_NOT_MEMORY         : 1;
    unsigned int ERR_ANTIOVERFLOW       : 1;
    unsigned int ERR_LEFT_CANARY        : 1;
    unsigned int ERR_RIGHT_CANARY       : 1;
    unsigned int ERR_HASH               : 1;
} err;      */

enum StackErr
{
    ERR_NOT_STACK          = 1028,
    ERR_NOT_DATA           = 1,
    ERR_INCORRECT_SIZE     = 2,
    ERR_INCORRECT_CAPACITY = 4,
    ERR_NOT_MEMORY         = 8,
    ERR_ANTIOVERFLOW       = 16,
    ERR_LEFT_CANARY        = 32,
    ERR_RIGHT_CANARY       = 64,
    ERR_HASH_STACK         = 128,
    ERR_HASH_DATA          = 256,
};

#endif
