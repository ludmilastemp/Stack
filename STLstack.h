#ifndef STL_stack_
#define STL_stack_

#include "STLstkconst.h"
#include "error.h"

int StackPush (Stack* stk, int value);
int StackPop  (Stack* stk, int* value);

int StackCtor (Stack* stk, size_t capacity = INITIAL_CAPACITY);
int StackDtor (Stack* stk);

#endif
