#ifndef STL_stack_struct_
#define STL_stack_struct_

#ifndef DBG_E

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#endif /* DBG_E */

/// тип кода ошибки
typedef int ErrorType;

#ifdef CANARY_PROTECTION
    typedef long long CanaryType;
    #define PRINT_CANARY "%d"
#endif

/// структура стека
struct Stack
{
#ifdef CANARY_PROTECTION
    CanaryType leftCanary;
#endif

    const char*  CREATE_FILE; // const???
    const size_t CREATE_LINE;
    const char*  CREATE_FUNC;
    const char*  CREATE_NAME;
    DataType* data;
    size_t size;
    size_t capacity;
    ErrorType err;

#ifdef HASH_PROTECTION
    long long hashStack;
    long long hashData;
#endif

#ifdef CANARY_PROTECTION
    CanaryType rightCanary;
#endif
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

/// возможные ошибки при работе с стеком
enum StackErr
{
    ERR_NOT_STACK          = 1 << 18,
    ERR_NOT_DATA           = 1 << 0,    // pointer != poison
    ERR_INCORRECT_SIZE     = 1 << 1,
    ERR_INCORRECT_CAPACITY = 1 << 2,
    ERR_NOT_MEMORY         = 1 << 3,
    ERR_ANTIOVERFLOW       = 1 << 4,

#ifdef CANARY_PROTECTION
    ERR_LEFT_CANARY        = 1 << 5,
    ERR_RIGHT_CANARY       = 1 << 6,
#endif

#ifdef CANARY_PROTECTION
    ERR_LEFT_CANARY_DATA   = 1 << 7,
    ERR_RIGHT_CANARY_DATA  = 1 << 8,
#endif

#ifdef HASH_PROTECTION
    ERR_HASH_STACK         = 1 << 9,
    ERR_HASH_DATA          = 1 << 10,
#endif
};

#define StackErr(stk) STL_StackErr (stk,       \
                                    CALL_FILE, \
                                    CALL_LINE, \
                                    CALL_FUNC)
#define StackDump(stk) STL_StackDump (stk,     \
                                    CALL_FILE, \
                                    CALL_LINE, \
                                    CALL_FUNC)

#endif
