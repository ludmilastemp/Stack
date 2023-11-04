#ifndef DBG_E

#include <stdarg.h>

#endif /* DBG_E */

#include "STL_stack.h"

static StackErrorType StackRealloc     (STACK* stk);
static StackErrorType StackReallocUp   (STACK* stk);
static StackErrorType StackReallocDown (STACK* stk);
static void STL_Print (const char* const fmt, ...);

/**
    \brief проверяет стек на корректность и выводит стек в случае ошибки
    \param stk указатель на стек
    \return код ошибки
*/
#ifdef STACK_DEBUG
    #define StackVERIFICATOR(stk)                                   \
    do {                                                            \
                                                                    \
        if (STL_StackVerificator ((stk)))                           \
        {                                                           \
            StackPrintErr (stk, STL_FSENT_ARGS);                    \
            StackDUMP (stk);                                        \
            return stk->err;                                        \
        }                                                           \
    } while (false)
#else
    #define StackVERIFICATOR(stk)                                   \
    do {                                                            \
                                                                    \
        if (STL_StackVerificator ((stk)))                           \
        {                                                           \
            StackPrintErr (stk);                                    \
            StackDUMP (stk);                                        \
            return stk->err;                                        \
        }                                                           \
    } while (false)
#endif

/**
    \brief вывести стек
    \param stk указатель на стек
    \return void
*/
#ifdef STACK_DEBUG
    #define StackDUMP(stk)                                          \
        STL_StackDump ((stk), STL_FSENT_ARGS);
#else
    #define StackDUMP(stk)                                          \
        STL_StackDump ((stk));
#endif

/**
    \brief проверяет стек на корректность
    \param stk указатель на стек
    \return код ошибки
*/
#define ReturnStackVerificator(stk)                                 \
        STL_StackVerificator ((stk))

StackErrorType
STL_StackCtor (STACK* stk

#ifdef STACK_DEBUG
               , const char* CREATE_NAME
               , STL_FREC_ARGS
#endif
               , size_t capacity)
{
    assert (stk);

#ifdef STACK_DEBUG
    stk->CREATE_FILE = CALL_FILE;
    stk->CREATE_LINE = CALL_LINE;
    stk->CREATE_FUNC = CALL_FUNC;
    stk->CREATE_NAME = CREATE_NAME;
#endif

    stk->size     = 0;
    stk->capacity = capacity;

    stk->err      = 0;

    StackRealloc (stk);

#ifdef STACK_CANARY_PROTECTION
    stk->leftCanary  = (CanaryType) (stk);
    stk->rightCanary = (CanaryType) (stk);
#endif

#ifdef STACK_HASH_PROTECTION
    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash ((char*) stk, sizeof (STACK));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (StackDataType) * stk->capacity);
#endif

    /**
     * Очистка файла
     */
    FILE* fp = fopen (logFile, "w");
    fclose (fp);
    fp = nullptr;

    return ReturnStackVerificator (stk);
}

StackErrorType
STL_StackDtor (STACK* stk

#ifdef STACK_DEBUG
              , STL_FREC_ARGS
#endif
              )
{
    assert (stk);

    StackVERIFICATOR (stk);

    stk->size        = INCORRECT_SIZE;
    stk->capacity    = 0;

#ifdef STACK_CANARY_PROTECTION
    stk->data        = (StackDataType*)((CanaryType*)(stk->data) - 1);
#endif

    free(stk->data);
    stk->data        = nullptr;
    stk->err         = 0;

#ifdef STACK_CANARY_PROTECTION
    stk->leftCanary  = 0;
    stk->rightCanary = 0;
#endif

#ifdef STACK_HASH_PROTECTION
    stk->hashStack   = 0;
    stk->hashData    = 0;
#endif

    return 0;
}

StackErrorType
STL_StackPush (STACK* stk,
               StackDataType value

#ifdef STACK_DEBUG
               , STL_FREC_ARGS
#endif
              )
{
    assert (stk);

    StackVERIFICATOR (stk);

    if (StackReallocUp (stk)) return ReturnStackVerificator (stk);

    stk->data[stk->size++] = value;

#ifdef STACK_HASH_PROTECTION
    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash (stk, sizeof (STACK));
    stk->hashData  = CountHash (stk->data, sizeof (StackDataType) * stk->capacity);
#endif

    return ReturnStackVerificator (stk);
}

StackErrorType
STL_StackPop (STACK* stk,
              StackDataType* value

#ifdef STACK_DEBUG
              , STL_FREC_ARGS
#endif
              )
{
    assert (stk);

    StackVERIFICATOR (stk);

    if (stk->size == 0)
    {
        stk->err = ERR_UNDERFLOW;
        return ReturnStackVerificator (stk);
    }

    if (StackReallocDown (stk)) return ReturnStackVerificator (stk);

    *value = stk->data[--(stk->size)];
    stk->data[stk->size] = INCORRECT_DATA;

#ifdef STACK_HASH_PROTECTION
    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash (stk, sizeof (STACK));
    stk->hashData  = CountHash (stk->data, sizeof (StackDataType) * stk->capacity);
#endif

    return ReturnStackVerificator (stk);
}

StackErrorType
STL_StackVerificator (STACK* stk)
{
    assert (stk);

    StackErrorType err = 0;

    if (stk->err == ERR_NOT_MEMORY)           err |= ERR_NOT_MEMORY;
    if (stk->err == ERR_UNDERFLOW)            err |= ERR_UNDERFLOW;
    if (!(stk->data))                         err |= ERR_NOT_DATA_POINTER;
    if (stk->size == INCORRECT_SIZE ||
        stk->size > stk->capacity)            err |= ERR_INCORRECT_SIZE;
    if (stk->capacity == 0 ||
        stk->capacity == INCORRECT_CAPACITY)  err |= ERR_INCORRECT_CAPACITY;

#ifdef STACK_CANARY_PROTECTION
    if (stk->leftCanary  != (CanaryType) stk) err |= ERR_LEFT_CANARY;
    if (stk->rightCanary != (CanaryType) stk) err |= ERR_RIGHT_CANARY;
#endif

#ifdef STACK_CANARY_PROTECTION
    if (*((CanaryType*)stk->data - 1)             != (CanaryType) (stk->data))
                                              err |= ERR_LEFT_CANARY_DATA;
    if (*(CanaryType*)(stk->data + stk->capacity) != (CanaryType) (stk->data))
                                              err |= ERR_RIGHT_CANARY_DATA;
#endif

#ifdef STACK_HASH_PROTECTION
    long long hashStackRef = stk->hashStack;
    long long hashDataRef  = stk->hashData;

    stk->hashStack = 0;
    stk->hashData  = 0;
    stk->err = 0;

    stk->hashStack = CountHash (stk, sizeof (STACK));
    stk->hashData  = CountHash (stk->data, sizeof (StackDataType) * stk->capacity);

    if (stk->hashStack != hashStackRef)       err |= ERR_HASH_STACK;
    if (stk->hashData  != hashDataRef)        err |= ERR_HASH_DATA;

    stk->hashStack = hashStackRef;
    stk->hashData  = hashDataRef;
#endif

    stk->err = err;

    return err;
}

void
STL_StackDump (const STACK* stk

#ifdef STACK_DEBUG
               , STL_FREC_ARGS
#endif
              )
{
    STL_Print ("\nStack [0x%p]\n", stk);

#ifdef STACK_DEBUG
    STL_Print ("\t %s   from %s %-3d %s\n",   STL_DUMP_ARGS);
    STL_Print ("\t called from %s %-3d %s\n", STL_FSENT_ARGS);
#endif

    STL_Print ("{\n");

    assert (stk);

    STL_Print ("\t size = %zd\n",     stk->size);
    STL_Print ("\t capacity = %zd\n", stk->capacity);
    STL_Print ("\t data = [0x%p]\n",  stk->data);
    STL_Print ("\t {\n");

    if (stk->data)
    {
        size_t i = 0;
        for (; i < stk->size; ++i)
        {
            if (stk->data[i] == INCORRECT_DATA)
                STL_Print ("\t\t *[%zd] = POISON\n", i);
            else
                STL_Print ("\t\t *[%zd] = " STACK_DATA_PRINT_SPECIFIER "\n", i, stk->data[i]);
        }
        for (; i < stk->capacity; ++i)
        {
            if (stk->data[i] == INCORRECT_DATA)
                STL_Print ("\t\t  [%zd] = POISON\n", i);
            else
                STL_Print ("\t\t  [%zd] = " STACK_DATA_PRINT_SPECIFIER "\n", i, stk->data[i]);
        }
    }

    STL_Print ("\t }\n");

#ifdef STACK_CANARY_PROTECTION
    STL_Print ("\t leftCanary      = [0x%p]\n", stk->leftCanary);
    STL_Print ("\t rightCanary     = [0x%p]\n", stk->rightCanary);
#endif

#ifdef STACK_HASH_PROTECTION
    STL_Print ("\t hashStack       = [0x%p]\n", stk->hashStack);
#endif

#ifdef STACK_CANARY_PROTECTION
    STL_Print ("\t leftCanaryData  = [0x%p]\n", *((CanaryType*)stk->data - 1));
    STL_Print ("\t rightCanaryData = [0x%p]\n", *(CanaryType*)(stk->data + stk->capacity));
#endif

#ifdef STACK_HASH_PROTECTION
    STL_Print ("\t hashData        = [0x%p]\n", stk->hashData);
#endif

    STL_Print ("}\n");
}

StackErrorType
StackRealloc (STACK* stk)
{
    assert (stk);

    size_t capacityNew = stk->capacity * sizeof (StackDataType);

#ifdef STACK_CANARY_PROTECTION
    capacityNew += 2 * sizeof (CanaryType);
    /**
     * [leftCanary][*data][rightCanary]
     */
#endif

    stk->data = (StackDataType*) realloc (stk->data, capacityNew);

    if (!stk->data)
    {
        stk->err = ERR_NOT_MEMORY;
        return stk->err;
    }

#ifdef STACK_CANARY_PROTECTION
    stk->data = (StackDataType*) ((CanaryType*)stk->data + 1);
#endif

#ifdef STACK_CANARY_PROTECTION
    *((CanaryType*)stk->data - 1)             = (CanaryType) (stk->data);
    *(CanaryType*)(stk->data + stk->capacity) = (CanaryType) (stk->data);
#endif

    for (size_t i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = INCORRECT_DATA;
    }

#ifdef STACK_HASH_PROTECTION
    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash ((char*) stk, sizeof (STACK));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (StackDataType) * stk->capacity);
#endif

    return stk->err;
}

StackErrorType
StackReallocUp (STACK* stk)
{
    assert (stk);

    if (stk->size < stk->capacity) return 0;

    $ printf ("I ReallocUp   size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    stk->capacity *= (size_t)EXPAND_MULTIPLIER;

#ifdef STACK_CANARY_PROTECTION
    stk->data = (StackDataType*) ((char*)stk->data - sizeof (CanaryType));
#endif

    if (StackRealloc (stk)) return stk->err;

    $ printf ("New --------- size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    return stk->err;
}

StackErrorType
StackReallocDown (STACK* stk)
{
    assert (stk);

    if ((stk->size - 1) * EXPAND_MULTIPLIER * EXPAND_MULTIPLIER > stk->capacity ||
        stk->size == 1) return 0;

    $ printf ("I ReallocDown size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    stk->capacity /= EXPAND_MULTIPLIER;

#ifdef STACK_CANARY_PROTECTION
    stk->data = (StackDataType*) ((char*)stk->data - sizeof (CanaryType));
#endif

    if (StackRealloc (stk)) return stk->err;

    $ printf ("New---------- size = %d  capacity = %d\n",
                        stk->size, stk->capacity);

    return stk->err;
}

static void STL_Print (const char* const fmt, ...)
{
    assert   (fmt);
    FILE* fp = fopen (logFile, "a");

    va_list   args = {};

    va_start (args, fmt);

    vfprintf (stderr, fmt, args);
    vfprintf (fp, fmt, args);

    va_end   (args);

    fclose   (fp);
    fp = nullptr;
}


#undef Verificator
