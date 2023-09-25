#ifndef STL_stack_
#define STL_stack_

#include "STL_stack_const.h"
#include "error.h"

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

int StackPush (Stack* stk, DataType  value, const char*  CALL_FILE,
                                            const size_t CALL_LINE,
                                            const char*  CALL_FUNC);
int StackPop  (Stack* stk, DataType* value);

int StackCtor (Stack* stk, size_t capacity = INITIAL_CAPACITY);
int StackDtor (Stack* stk);

#endif