#include "STLstack.h"

static int StackReallocUp   (Stack* stk);
static int StackReallocDown (Stack* stk);

int StackPush (Stack* stk, int value)
{
    if (STACK_ERR(stk)) return stk->err;

    if (StackReallocUp (stk)) return stk->err;

    stk->data[stk->size++] = value;

    return 0;
}

int StackPop (Stack* stk, int* value)
{
    if (STACK_ERR(stk)) return stk->err;

    if (stk->size == 0)
    {
        stk->err = ERR_ANTIOVERFLOW;
        return stk->err;
    }

    if (StackReallocDown (stk)) return stk->err;

    *value = stk->data[--(stk->size)];
    stk->data[stk->size] = INCORRECT_DATA;

    return 0;
}

int StackReallocUp (Stack* stk)
{
    if (stk->size < stk->capacity) return 0;

    $ printf ("I ReallocUp   size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    stk->capacity *= EXPAND_MULTIPLIER;
    stk->data = (int*) realloc (stk->data, sizeof (int) * stk->capacity);

    for (size_t i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = INCORRECT_DATA;
    }

    $ printf ("New --------- size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    return STACK_ERR(stk);
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

    return STACK_ERR(stk);
}
