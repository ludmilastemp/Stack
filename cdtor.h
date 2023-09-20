#ifndef STL_cdtor_
#define STL_cdtor_

#include "error.h"

const size_t INITIAL_CAPACITY = 1;

int StackCtor (Stack* stk, size_t capacity = INITIAL_CAPACITY);

int StackDtor (Stack* stk);

int StackCtor (Stack* stk, size_t capacity)
{
    if (!stk) return 1;

    stk->size     = 0;
    stk->capacity = capacity;
    stk->data     = (int*) calloc (stk->capacity, sizeof (int));
    stk->err      = 0;

    if (!StackErr(stk)) return 0;
}

int StackDtor (Stack* stk)
{
    if (!stk) return 1;

    stk->size     = 0;
    stk->capacity = 0;
    free(stk->data);
    stk->data     = nullptr;
    stk->err      = 0;

    return 0;
}

#endif
