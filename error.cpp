#include "error.h"

#ifndef DBG_E

#include <string.h>
#include <stdarg.h>

#endif /* DBG_E */

static char errStr[500] = "Error from ";

static void STL_Print (const char* const fmt, ...);

#ifdef HASH_PROTECTION
long long
CountHash (void* data, long long size)
{
    long long hash = 0;

    $ printf ("I CountHash: *data = [%p], size = %d\n", data, size);

    for (size_t i = 0; i < size; ++i)
    {
        hash += ((char*)data)[i];
        $ printf ("%-2d %-4d %-4d  ", i, ((char*)data)[i], hash);
    }

    $ printf ("hash = %ld\n", hash);

    return hash;
}
#endif

ErrorType
STL_Verificator (Stack* stk)
{
    assert (stk);

    ErrorType err = 0;

    if (stk->err == ERR_NOT_MEMORY)           err |= ERR_NOT_MEMORY;
    if (stk->err == ERR_ANTIOVERFLOW)         err |= ERR_ANTIOVERFLOW;
    if (!(stk->data))                         err |= ERR_NOT_DATA_POINTER;
    if (stk->size == INCORRECT_SIZE ||
        stk->size > stk->capacity)            err |= ERR_INCORRECT_SIZE;
    if (stk->capacity == 0 ||
        stk->capacity == INCORRECT_CAPACITY)  err |= ERR_INCORRECT_CAPACITY;

#ifdef CANARY_PROTECTION
    if (stk->leftCanary  != (CanaryType) stk) err |= ERR_LEFT_CANARY;
    if (stk->rightCanary != (CanaryType) stk) err |= ERR_RIGHT_CANARY;
#endif

#ifdef CANARY_PROTECTION
    if (*(CanaryType*)(stk->data + stk->capacity) != (CanaryType) (stk->data))
                                              err |= ERR_LEFT_CANARY_DATA;
    if (*(CanaryType*)(stk->data + stk->capacity) != (CanaryType) (stk->data))
                                              err |= ERR_RIGHT_CANARY_DATA;
#endif

#ifdef HASH_PROTECTION
    long long hashStackRef = stk->hashStack;
    long long hashDataRef  = stk->hashData;

    stk->hashStack = 0;
    stk->hashData  = 0;
    stk->err = 0;

    stk->hashStack = CountHash (stk, sizeof (Stack));
    stk->hashData  = CountHash (stk->data, sizeof (DataType) * stk->capacity);

    if (stk->hashStack != hashStackRef)       err |= ERR_HASH_STACK;
    if (stk->hashData  != hashDataRef)        err |= ERR_HASH_DATA;

    stk->hashStack = hashStackRef;
    stk->hashData  = hashDataRef;
#endif

    stk->err = err;

    return err;
}

void
STL_StackDump (const Stack* stk

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
              )
{
    STL_Print ("\nStack [0x%p]\n", stk);

#ifdef DEBUG
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

#ifdef CANARY_PROTECTION
    STL_Print ("\t leftCanary      = [0x%p]\n", stk->leftCanary);
    STL_Print ("\t rightCanary     = [0x%p]\n", stk->rightCanary);
#endif

#ifdef HASH_PROTECTION
    STL_Print ("\t hashStack       = [0x%p]\n", stk->hashStack);
#endif

#ifdef CANARY_PROTECTION
    STL_Print ("\t leftCanaryData  = [0x%p]\n", *((CanaryType*)stk->data - 1));
    STL_Print ("\t rightCanaryData = [0x%p]\n", *(CanaryType*)(stk->data + stk->capacity));
#endif

#ifdef HASH_PROTECTION
    STL_Print ("\t hashData        = [0x%p]\n", stk->hashData);
#endif

    STL_Print ("}\n");
}

char*
StackPrintErr (const Stack* stk

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
               )
{
    char str[100] = " ";

    sprintf (errStr, "\n\n"

#ifdef DEBUG
             "Error from %s %-3d %s()\n", STL_FSENT_ARGS
#endif
            );

    if (stk->err % (2 * ERR_NOT_DATA_POINTER)   >= ERR_NOT_DATA_POINTER)
    {
        sprintf (str, "ERROR! incorrect *data = %p\n", stk->data);
        strcat (errStr, str);
    }
    if (stk->err % (2 * ERR_NOT_MEMORY)         >= ERR_NOT_MEMORY)
    {
        sprintf (str, "ERROR! not memory\n");
        strcat (errStr, str);
    }
    if (stk->err % (2 * ERR_ANTIOVERFLOW)       >= ERR_ANTIOVERFLOW)
    {
        sprintf (str, "ERROR! antioverflow\n");
        strcat (errStr, str);
    }
    if (stk->err % (2 * ERR_INCORRECT_SIZE)     >= ERR_INCORRECT_SIZE)
    {
        sprintf (str, "ERROR! incorrect size = %zd\n", stk->size);
        strcat (errStr, str);
    }
    if (stk->err % (2 * ERR_INCORRECT_CAPACITY) >= ERR_INCORRECT_CAPACITY)
    {
        sprintf (str, "ERROR! incorrect capacity = %zd\n", stk->capacity);
        strcat (errStr, str);
    }

#ifdef CANARY_PROTECTION
    if (stk->err % (2 * ERR_LEFT_CANARY)        >= ERR_LEFT_CANARY)
    {
        sprintf (str, "ERROR! incorrect leftCanary = [0x%p]\n", stk->leftCanary);
        strcat (errStr, str);
    }
    if (stk->err % (2 * ERR_RIGHT_CANARY)       >= ERR_RIGHT_CANARY)
    {
        sprintf (str, "ERROR! incorrect rightCanary = [0x%p]\n", stk->rightCanary);
        strcat (errStr, str);
    }
#endif

#ifdef CANARY_PROTECTION
    if (stk->err % (2 * ERR_LEFT_CANARY_DATA)   >= ERR_LEFT_CANARY_DATA)
    {
        sprintf (str, "ERROR! incorrect leftCanaryData = [0x%p]\n", *((CanaryType*)stk->data - 1));
        strcat (errStr, str);
    }
    if (stk->err % (2 * ERR_RIGHT_CANARY_DATA)  >= ERR_RIGHT_CANARY_DATA)
    {
        sprintf (str, "ERROR! incorrect rightCanaryData = [0x%p]\n", *(CanaryType*)(stk->data + stk->capacity));
        strcat (errStr, str);
    }
#endif

#ifdef HASH_PROTECTION
    if (stk->err % (2 * ERR_HASH_STACK)         >= ERR_HASH_STACK)
    {
        sprintf (str, "ERROR! incorrect hashStack = [0x%p]\n", stk->hashStack);
        strcat (errStr, str);
    }
    if (stk->err % (2 * ERR_HASH_DATA)          >= ERR_HASH_DATA)
    {
        sprintf (str, "ERROR! incorrect hashData  = [0x%p]\n", stk->hashData);
        strcat (errStr, str);
    }
#endif

    STL_Print ("%s", errStr);

    return errStr;
}

static void STL_Print (const char* const fmt, ...)
{
    assert (fmt);
    FILE* fp = fopen (logFile, "a");

    va_list args = {};

    va_start (args, fmt);

    vfprintf (stderr, fmt, args);
    vfprintf (fp, fmt, args);

    va_end (args);

    fclose   (fp);
    fp = nullptr;
}
