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

    Verificator (stk);

    if (StackReallocUp (stk)) return ReturnVerificator (stk);

    stk->data[stk->size++] = value;

#ifdef HASH_PROTECTION
    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash (stk, sizeof (Stack));
    stk->hashData  = CountHash (stk->data, sizeof (DataType) * stk->capacity);
#endif

    return ReturnVerificator (stk);
}

ErrorType
STL_StackPop (Stack* stk, DataType* value,
                          const char*  CALL_FILE,
                          const size_t CALL_LINE,
                          const char*  CALL_FUNC)
{
    assert (stk);

    Verificator (stk);

    if (stk->size == 0)
    {
        stk->err = ERR_ANTIOVERFLOW;
        return ReturnVerificator (stk);
    }

    if (StackReallocDown (stk)) return ReturnVerificator (stk);

    *value = stk->data[(stk->size)--];
    stk->data[stk->size] = INCORRECT_DATA;

#ifdef HASH_PROTECTION
    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash (stk, sizeof (Stack));
    stk->hashData  = CountHash (stk->data, sizeof (DataType) * stk->capacity);
#endif

    return ReturnVerificator (stk);
}

ErrorType
STL_StackCtor (Stack* stk, const char*  CREATE_NAME,
                           const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC,
                           size_t capacity)
{
    assert (stk);

    stk->CREATE_NAME = CREATE_NAME;
    stk->size     = 0;
    stk->capacity = capacity;
    stk->err      = 0;

    StackRealloc (stk);

#ifdef CANARY_PROTECTION
    stk->leftCanary  = (CanaryType) (stk);
    stk->rightCanary = (CanaryType) (stk);
#endif

#ifdef HASH_PROTECTION
    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash ((char*) stk, sizeof (Stack));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);
#endif

    return ReturnVerificator (stk);
}

ErrorType
STL_StackDtor (Stack* stk, const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC)
{
    assert (stk);

    Verificator (stk);

    stk->size        = INCORRECT_SIZE;
    stk->capacity    = 0;

#ifdef CANARY_PROTECTION
    stk->data        = (DataType*)((CanaryType*)(stk->data) - 1);
#endif

    free(stk->data);
    stk->data        = nullptr;
    stk->err         = 0;

#ifdef CANARY_PROTECTION
    stk->leftCanary  = 0;
    stk->rightCanary = 0;
#endif

#ifdef HASH_PROTECTION
    stk->hashStack   = 0;
    stk->hashData    = 0;
#endif

    return 0;
}

ErrorType
StackRealloc (Stack* stk)
{
    assert (stk);

    size_t capacityNew = stk->capacity * sizeof (DataType);

#ifdef CANARY_PROTECTION
    capacityNew += 2 * sizeof (CanaryType);
    /**
     * [leftCanary][*data][rightCanary]
     */
#endif

    stk->data = (DataType*) realloc (stk->data, capacityNew);

    if (!stk->data)
    {
        stk->err = ERR_NOT_MEMORY;
        return stk->err;
    }

#ifdef CANARY_PROTECTION
    stk->data = (DataType*) ((CanaryType*)stk->data + 1);
#endif

#ifdef CANARY_PROTECTION
    *((CanaryType*)stk->data - 1)             = (CanaryType) (stk->data);
    *(CanaryType*)(stk->data + stk->capacity) = (CanaryType) (stk->data);
#endif

    for (size_t i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = INCORRECT_DATA;
    }

#ifdef HASH_PROTECTION
    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash ((char*) stk, sizeof (Stack));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);
#endif

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

#ifdef CANARY_PROTECTION
    stk->data = (DataType*) ((char*)stk->data - sizeof (CanaryType));
#endif

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

#ifdef CANARY_PROTECTION
    stk->data = (DataType*) ((char*)stk->data - sizeof (CanaryType));
#endif

    if (StackRealloc (stk)) return stk->err;

    $ printf ("New---------- size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    return stk->err;
}
