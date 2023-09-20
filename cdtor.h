#ifndef STL_cdtor_
#define STL_cdtor_

#include "error.h"

const size_t INITIALCAPACITY = 8;

int StackCtor (Stack* stk, size_t capacity = INITIALCAPACITY);

int StackDtor (Stack* stk);

int StackCtor (Stack* stk, size_t capacity)
{
    if (!stk) return 0;

    stk->size     = 0;
    stk->capacity = capacity;
    stk->data     = (int*) calloc (stk->capacity, sizeof (int));
    stk->err      = 0;

    if (!StackErr(stk)) return 1;
}

int StackDtor (Stack* stk)
{
    if (!stk) return 0;

    stk->size     = 0;
    stk->capacity = 0;
    free(stk->data);
    stk->data     = nullptr;
    stk->err      = 0;
}

#endif
