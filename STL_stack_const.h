#ifndef STL_stack_const_
#define STL_stack_const_

#ifndef DBG_E

#include <stdio.h>
#include <stdlib.h>

#endif /* DBG_E */

const int DEBUG = 1;
#define $ if (DEBUG) // $printf()

#ifndef STACK_T
#define STACK_T int
#endif /* STACK_T */

typedef STACK_T DataType;


#define PRINT_DATA "%d"

typedef long long CanaryType;
#define PRINT_CANARY "%d"

const size_t INITIAL_CAPACITY  = 1; // DEFINE_STACK_INITIAL_CAPACITY;
const size_t EXPAND_MULTIPLIER = 2; // Bit shift << >> :)

const size_t INCORRECT_SIZE = -1u;
const int    INCORRECT_DATA = 666;

#define StackErr(stk) STL_StackErr (stk,       \
                                    CALL_FILE, \
                                    CALL_LINE, \
                                    CALL_FUNC)
#define StackDump(stk) STL_StackDump (stk,     \
                                    CALL_FILE, \
                                    CALL_LINE, \
                                    CALL_FUNC)

#endif
