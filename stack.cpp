#include "STL_stack.h"

static ErrorType StackRealloc     (Stack* stk);
static ErrorType StackReallocUp   (Stack* stk);
static ErrorType StackReallocDown (Stack* stk);

ErrorType
STL_StackPush (Stack* stk, DataType value,
                           const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC)
{
    assert (stk);

    if (StackErr (stk)) return stk->err;

    if (StackReallocUp (stk)) return StackErr (stk);

    stk->data[stk->size++] = value;

    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash (stk, sizeof (Stack));
    stk->hashData  = CountHash (stk->data, sizeof (DataType) * stk->capacity);

    return StackErr (stk);
}

ErrorType
STL_StackPop (Stack* stk, DataType* value,
                          const char*  CALL_FILE,
                          const size_t CALL_LINE,
                          const char*  CALL_FUNC)
{
    assert (stk);

    if (StackErr (stk)) return stk->err;

    if (stk->size == 0)
    {
        stk->err = ERR_ANTIOVERFLOW;
        return StackErr (stk);
    }

    if (StackReallocDown (stk)) return StackErr (stk);

    *value = stk->data[--(stk->size)];
    stk->data[stk->size] = INCORRECT_DATA;

    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash (stk, sizeof (Stack));
    stk->hashData  = CountHash (stk->data, sizeof (DataType) * stk->capacity);

    return StackErr (stk);
}

ErrorType
STL_StackCtor (Stack* stk, const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC,
                           size_t capacity)
{
    assert (stk);

    stk->size     = 0;
    stk->capacity = capacity;
    stk->err      = 0;

    StackRealloc (stk);

    stk->leftCanary  = (CanaryType) (stk);
    stk->rightCanary = (CanaryType) (stk);

    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash ((char*) stk, sizeof (Stack));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);


    return StackErr (stk);
}

ErrorType
STL_StackDtor (Stack* stk, const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC)
{
    assert (stk);

    if (StackErr (stk)) return stk->err;

    stk->size        = INCORRECT_SIZE;
    stk->capacity    = 0;
    stk->data        = (DataType*)((CanaryType*)(stk->data) - 1);
    free(stk->data);
    stk->data        = nullptr;
    stk->err         = 0;
    stk->leftCanary  = 0;
    stk->rightCanary = 0;
    stk->hashStack   = 0;
    stk->hashData    = 0;

    return 0;
}

ErrorType
StackRealloc (Stack* stk)
{
    assert (stk);

    /**
     * [leftCanary][*data][rightCanary]
     */
    stk->data = (DataType*) realloc (stk->data, stk->capacity * sizeof (DataType) +
                                    2 * sizeof (CanaryType));

    if (!stk->data)
    {
        stk->err = ERR_NOT_MEMORY;
        return stk->err;
    }

    stk->data = (DataType*) ((CanaryType*)stk->data + 1);

    *((CanaryType*)stk->data - 1)             = (CanaryType) (stk->data);
    *(CanaryType*)(stk->data + stk->capacity) = (CanaryType) (stk->data);

    for (size_t i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = INCORRECT_DATA;
    }

    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash ((char*) stk, sizeof (Stack));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);

    return stk->err;
}

ErrorType
StackReallocUp (Stack* stk)
{
    assert (stk);

    if (stk->size < stk->capacity) return 0;

    $ printf ("I ReallocUp   size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    stk->capacity *= EXPAND_MULTIPLIER;

    stk->data = (DataType*) ((char*)stk->data - sizeof (CanaryType));

    if (StackRealloc (stk)) return stk->err;

    $ printf ("New --------- size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    return stk->err;
}

ErrorType
StackReallocDown (Stack* stk)
{
    assert (stk);

    if ((stk->size - 1) * EXPAND_MULTIPLIER * EXPAND_MULTIPLIER > stk->capacity ||
        stk->size == 1) return 0;

    $ printf ("I ReallocDown size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    stk->capacity /= EXPAND_MULTIPLIER;

    stk->data = (DataType*) ((char*)stk->data - sizeof (CanaryType));

    if (StackRealloc (stk)) return stk->err;

    $ printf ("New---------- size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    return stk->err;
}
