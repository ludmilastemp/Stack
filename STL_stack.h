#ifndef STL_stack_
#define STL_stack_

#include "STL_stack_const.h"
#include "error.h"

struct Stack
{
    CanaryType leftCanary;
#if 1
    const char*  CREATE_FILE; // const???
    const size_t CREATE_LINE;
    const char*  CREATE_FUNC;
#endif
    DataType* data;
    size_t size;
    size_t capacity;
    long long err;
    long long hashStack;
    long long hashData;
    CanaryType rightCanary;
};

/*  test it    attribute (packed)
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
    ERR_NOT_STACK          = 1028, // 1 << 10
    ERR_NOT_DATA           = 1,    // 1 << 0
    ERR_INCORRECT_SIZE     = 2,
    ERR_INCORRECT_CAPACITY = 4,
    ERR_NOT_MEMORY         = 8,
    ERR_ANTIOVERFLOW       = 16,
    ERR_LEFT_CANARY        = 32,
    ERR_RIGHT_CANARY       = 64,
    ERR_HASH_STACK         = 128,
    ERR_HASH_DATA          = 256,
};

typedef int StackErr_t;

StackErr_t
STL_StackPush (Stack* stk, DataType  value,
                               const char*  CALL_FILE,
                               const size_t CALL_LINE,
                               const char*  CALL_FUNC);
int
STL_StackPop  (Stack* stk, DataType* value,
                               const char*  CALL_FILE,
                               const size_t CALL_LINE,
                               const char*  CALL_FUNC);

int STL_StackCtor (Stack* stk, const char*  CALL_FILE,
                               const size_t CALL_LINE,
                               const char*  CALL_FUNC,
                   size_t capacity = INITIAL_CAPACITY);

int STL_StackDtor (Stack* stk, const char*  CALL_FILE,
                               const size_t CALL_LINE,
                               const char*  CALL_FUNC);

#endif
