//#ifndef STL_stack_struct_
//#define STL_stack_struct_

#ifndef DBG_E

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#endif /* DBG_E */

/// тип кода ошибки
typedef int StackErrorType;

#ifdef STACK_CANARY_PROTECTION
    typedef long long CanaryType;
    #define CANARY_PRINT_SPECIFIER "%d"
#endif

/// структура стека
struct STACK
{
#ifdef STACK_CANARY_PROTECTION
    CanaryType leftCanary;
#endif

#ifdef STACK_DEBUG
    size_t       CREATE_LINE;
    const char*  CREATE_FILE;
    const char*  CREATE_FUNC;
    const char*  CREATE_NAME;
#endif

    StackDataType* data;
    size_t size;
    size_t capacity;
    StackErrorType err;

#ifdef STACK_HASH_PROTECTION
    long long hashStack;
    long long hashData;
#endif

#ifdef STACK_CANARY_PROTECTION
    CanaryType rightCanary;
#endif
};

/// возможные ошибки при работе с стеком
enum StackErr
{
    ERR_NOT_STACK_POINTER  = 1 << 18,
    ERR_NOT_DATA_POINTER   = 1 << 0,
    ERR_INCORRECT_SIZE     = 1 << 1,
    ERR_INCORRECT_CAPACITY = 1 << 2,
    ERR_NOT_MEMORY         = 1 << 3,
    ERR_UNDERFLOW          = 1 << 4,

#ifdef STACK_CANARY_PROTECTION
    ERR_LEFT_CANARY        = 1 << 5,
    ERR_RIGHT_CANARY       = 1 << 6,
#endif

#ifdef STACK_CANARY_PROTECTION
    ERR_LEFT_CANARY_DATA   = 1 << 7,
    ERR_RIGHT_CANARY_DATA  = 1 << 8,
#endif

#ifdef STACK_HASH_PROTECTION
    ERR_HASH_STACK         = 1 << 9,
    ERR_HASH_DATA          = 1 << 10,
#endif
};

//#endif /* STL_stack_struct_ */
