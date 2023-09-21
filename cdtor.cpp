#include "STLstack.h"

int StackCtor (Stack* stk, size_t capacity)
{
    if (!stk)
    {
        return 1;
    }

    stk->size     = 0;
    stk->capacity = capacity;
    stk->data     = (int*) calloc (stk->capacity, sizeof (int));
    stk->err      = 0;

    for (size_t i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = INCORRECT_DATA;
    }

    return STACK_ERR(stk);
}

int StackDtor (Stack* stk)
{
    if (STACK_ERR(stk)) return stk->err;

    stk->size     = INCORRECT_SIZE;
    stk->capacity = 0;
    free(stk->data);
    stk->data     = nullptr;
    stk->err      = 0;

    return 0;
}
