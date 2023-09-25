#include "STL_stack.h"

static int StackReallocUp   (Stack* stk);
static int StackReallocDown (Stack* stk);

int StackPush (Stack* stk, DataType value, const char*  CALL_FILE,
                                           const size_t CALL_LINE,
                                           const char*  CALL_FUNC)
{
    if (STACK_ERR (stk)) return stk->err;

    if (StackReallocUp (stk)) return stk->err;

    stk->data[stk->size++] = value;

    stk->hashData = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);

    return 0;
}

int StackPop (Stack* stk, DataType* value)
{
    if (STACK_ERR (stk)) return stk->err;

    if (stk->size == 0)
    {
        stk->err = ERR_ANTIOVERFLOW;
        return stk->err;
    }

    if (StackReallocDown (stk)) return stk->err;

    *value = stk->data[--(stk->size)];
    stk->data[stk->size] = INCORRECT_DATA;

    stk->hashData = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);

    return 0;
}

int StackReallocUp (Stack* stk)
{
    if (stk->size < stk->capacity) return 0;

    $ printf ("I ReallocUp   size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    stk->capacity *= EXPAND_MULTIPLIER;

    stk->data = (DataType*) ((char*)stk->data - sizeof (CanaryType));

    stk->data = (DataType*) realloc (stk->data, stk->capacity * sizeof (DataType) +
                                    2 * sizeof (CanaryType));

    if (!stk->data)
    {
        stk->err = ERR_NOT_MEMORY;
        return stk->err;
    }

    stk->data = (DataType*) ((char*)stk->data + sizeof (CanaryType));

    *((CanaryType*)stk->data - 1) = (CanaryType) (stk->data);
    *(CanaryType*) (stk->data + stk->capacity) = (CanaryType) (stk->data);

    for (size_t i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = INCORRECT_DATA;
    }

    stk->hashStack = CountHash ((char*) stk, sizeof (Stack));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);

    $ printf ("New --------- size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    return STACK_ERR (stk);
}

int StackReallocDown (Stack* stk)
{
    if (stk->size >= stk->capacity / EXPAND_MULTIPLIER) return 0;

    $ printf ("I ReallocDown size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    stk->capacity /= EXPAND_MULTIPLIER;

    stk->data = (DataType*) ((char*)stk->data - sizeof (CanaryType));

    stk->data = (DataType*) realloc (stk->data, stk->capacity * sizeof (DataType) +
                                    2 * sizeof (CanaryType));

    if (!stk->data)
    {
        stk->err = ERR_NOT_MEMORY;
        return stk->err;
    }

    stk->data = (DataType*) ((char*)stk->data + sizeof (CanaryType));

    *((CanaryType*)stk->data - 1) = (CanaryType) (stk->data);
    *(CanaryType*) (stk->data + stk->capacity) = (CanaryType) (stk->data);

    stk->hashStack = CountHash ((char*) stk, sizeof (Stack));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);

    $ printf ("New---------- size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    return STACK_ERR (stk);
}
