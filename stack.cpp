#include "STL_stack.h"

static ErrorType StackRealloc     (STACK* stk);
static ErrorType StackReallocUp   (STACK* stk);
static ErrorType StackReallocDown (STACK* stk);

/**
    \brief проверяет стек на корректность и выводит стек в случае ошибки
    \param stk указатель на стек
    \return код ошибки
*/

#ifdef DEBUG
    #define Verificator(stk)                                        \
    do {                                                            \
                                                                    \
        if (STL_Verificator ((stk)))                                \
        {                                                           \
                                                                    \
            StackPrintErr (stk, STL_FSENT_ARGS);                    \
            STL_StackDump ((stk), STL_FSENT_ARGS);                  \
            return stk->err;                                        \
        }                                                           \
    } while (false)
#else
    #define Verificator(stk)                                        \
    do {                                                            \
                                                                    \
        if (STL_Verificator ((stk)))                                \
        {                                                           \
            StackPrintErr (stk);                                    \
            STL_StackDump ((stk));                                  \
            return stk->err;                                        \
        }                                                           \
    } while (false)
#endif

ErrorType
STL_StackCtor (STACK* stk

#ifdef DEBUG
               , const char* CREATE_NAME
               , STL_FREC_ARGS
#endif
               , size_t capacity)
{
    assert (stk);

#ifdef DEBUG
    stk->CREATE_FILE = CALL_FILE;
    stk->CREATE_LINE = CALL_LINE;
    stk->CREATE_FUNC = CALL_FUNC;
    stk->CREATE_NAME = CREATE_NAME;
#endif

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

    stk->hashStack = CountHash ((char*) stk, sizeof (STACK));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);
#endif

    /**
     * Очистка файла
     */
    FILE* fp = fopen (logFile, "w");
    fclose (fp);
    fp = nullptr;

    return ReturnVerificator (stk);
}

ErrorType
STL_StackDtor (STACK* stk

#ifdef DEBUG
              , STL_FREC_ARGS
#endif
              )
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
STL_StackPush (STACK* stk,
               DataType value

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
              )
{
    assert (stk);

    Verificator (stk);

    if (StackReallocUp (stk)) return ReturnVerificator (stk);

    stk->data[stk->size++] = value;

#ifdef HASH_PROTECTION
    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash (stk, sizeof (STACK));
    stk->hashData  = CountHash (stk->data, sizeof (DataType) * stk->capacity - 1);
#endif

    return ReturnVerificator (stk);
}

ErrorType
STL_StackPop (STACK* stk,
              DataType* value

#ifdef DEBUG
              , STL_FREC_ARGS
#endif
              )
{
    assert (stk);

    Verificator (stk);

    if (stk->size == 0)
    {
        stk->err = ERR_ANTIOVERFLOW;
        return ReturnVerificator (stk);
    }

    if (StackReallocDown (stk)) return ReturnVerificator (stk);

    *value = stk->data[--(stk->size)];
    stk->data[stk->size] = INCORRECT_DATA;

#ifdef HASH_PROTECTION
    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash (stk, sizeof (STACK));
    stk->hashData  = CountHash (stk->data, sizeof (DataType) * stk->capacity);
#endif

    return ReturnVerificator (stk);
}

ErrorType
StackRealloc (STACK* stk)
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

    stk->hashStack = CountHash ((char*) stk, sizeof (STACK));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);
#endif

    return stk->err;
}

ErrorType
StackReallocUp (STACK* stk)
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
StackReallocDown (STACK* stk)
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

#undef Verificator
