#ifndef STL_stack_
#define STL_stack_

#include "error.h"

const int DEBAG = 0;
#define $ if (DEBAG)

const size_t EXPAND_MULTIPLIER = 2;

int StackPush (Stack* stk, int value);

int StackPop  (Stack* stk, int* value);

int StackReallocUp (Stack* stk);

int StackReallocDown (Stack* stk);

int StackPush (Stack* stk, int value)
{
    if (StackErr(stk)) return 1;

    if (StackReallocUp(stk)) return 1;

    stk->data[stk->size++] = value;
    return 0;
}

int StackPop (Stack* stk, int* value)
{
    if (StackErr(stk)) return 1;

    if (stk->size == 0) return 1;

    if (StackReallocDown(stk)) return 1;

    *value = stk->data[stk->size];
    stk->data[--(stk->size)] = 0;
    return 0;
}

int StackReallocUp (Stack* stk)
{
    if (stk->size < stk->capacity) return 0;

    $ printf ("I ReallocUp   size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    stk->capacity *= EXPAND_MULTIPLIER;
    stk->data = (int*) realloc (stk->data, sizeof (int) * stk->capacity);

    $ printf ("New --------- size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    if (!(stk->data)) return 1;
    return 0;
}

int StackReallocDown (Stack* stk)
{
    if (stk->size >= stk->capacity / EXPAND_MULTIPLIER) return 0;

    $ printf ("I ReallocDown size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    stk->capacity /= EXPAND_MULTIPLIER;
    stk->data = (int*) realloc (stk->data, sizeof (int) * stk->capacity);

    $ printf ("New---------- size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    if (!(stk->data)) return 1;
    return 0;
}

#endif
