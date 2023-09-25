#ifndef STL_stack_const_
#define STL_stack_const_

#include <stdio.h>
#include <stdlib.h>

const int DEBUG = 0;
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

//#define STACK_ERR(stk)  StackErr (stk, CALL_FILE, CALL_LINE, CALL_FUNC)
//#define STACK_DUMP(stk) StackDump (stk, CALL_FILE, CALL_LINE, CALL_FUNC)
//#define StackCtor(stk)  StackCtor (stk, CALL_FILE, CALL_LINE, CALL_FUNC)
//#define StackDtor(stk) StackDump (stk, CALL_FILE, CALL_LINE, CALL_FUNC)


#endif