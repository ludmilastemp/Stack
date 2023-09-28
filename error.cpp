#include "error.h"

#ifndef DBG_E

#include <string.h>

#endif /* DBG_E */

static char errStr[500] = "Error from ";

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

void
STL_StackDump (const Stack* stk, const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC)
{
    printf ("\nStack [0x%p]\n", stk);
    printf ("\t %s   from %-3d %s %s\n",   stk->CREATE_NAME,
                                           stk->CREATE_LINE,
                                           stk->CREATE_FILE,
                                           stk->CREATE_FUNC);
    printf ("\t called from %-3d %s %s\n", CALL_LINE,
                                           CALL_FILE,
                                           CALL_FUNC);
    printf ("{\n");

    assert (stk);

    printf ("\t size = %zd\n",     stk->size);
    printf ("\t capacity = %zd\n", stk->capacity);
    printf ("\t data = [0x%p]\n",    stk->data);
    printf ("\t {\n");

    if (stk->data)
    {
        size_t i = 0;
        for (; i < stk->size; ++i)
        {
            if (stk->data[i] == INCORRECT_DATA)
                printf ("\t\t *[%zd] = POISON\n", i);
            else
                printf ("\t\t *[%zd] = " PRINT_DATA "\n", i, stk->data[i]);
        }
        for (; i < stk->capacity; ++i)
        {
            if (stk->data[i] == INCORRECT_DATA)
                printf ("\t\t  [%zd] = POISON\n", i);
            else
                printf ("\t\t  [%zd] = " PRINT_DATA "\n", i, stk->data[i]);
        }
    }

    printf ("\t }\n");

#ifdef CANARY_PROTECTION
    printf ("\t leftCanary  = [0x%p]\n", stk->leftCanary);
    printf ("\t rightCanary = [0x%p]\n", stk->rightCanary);
#endif

#ifdef HASH_PROTECTION
    printf ("\t hashStack = [0x%p]\n",      stk->hashStack);
#endif

#ifdef CANARY_PROTECTION
    printf ("\t leftCanaryData  = [0x%p]\n", *((CanaryType*)stk->data - 1));
    printf ("\t rightCanaryData = [0x%p]\n", *(CanaryType*)(stk->data + stk->capacity));
#endif

#ifdef HASH_PROTECTION
    printf ("\t hashData  = [0x%p]\n",      stk->hashData);
#endif

    printf ("}\n");
}

ErrorType
STL_Verificator (Stack* stk, const char*  CALL_FILE,
                             const size_t CALL_LINE,
                             const char*  CALL_FUNC)
{
    assert (stk);

    ErrorType err = 0;

    if (stk->err == ERR_NOT_MEMORY)           err |= ERR_NOT_MEMORY;
    if (stk->err == ERR_ANTIOVERFLOW)         err |= ERR_ANTIOVERFLOW;
    if (!(stk->data))                         err |= ERR_NOT_DATA;
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
#endif

    stk->err = err;

    if (!err) return 0;

    return err;
}

char*
StackPrintErr (const Stack* stk, const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC)
{    /*
    ERR_NOT_STACK          = 1 << 18,
    ERR_NOT_DATA           = 1 << 0,
    ERR_INCORRECT_SIZE     = 1 << 1,
    ERR_INCORRECT_CAPACITY = 1 << 2,
    ERR_NOT_MEMORY         = 1 << 3,
    ERR_ANTIOVERFLOW       = 1 << 4,
    ERR_LEFT_CANARY        = 1 << 5,
    ERR_RIGHT_CANARY       = 1 << 6,
    ERR_LEFT_CANARY_DATA   = 1 << 7,
    ERR_RIGHT_CANARY_DATA  = 1 << 8,
    ERR_HASH_STACK         = 1 << 9,
    ERR_HASH_DATA          = 1 << 10, */

    char str[100] = " ";

    sprintf (errStr, "\n\nError from %-3d %s %s()\n", CALL_LINE, CALL_FILE, CALL_FUNC);
    if (stk->err % (2 * ERR_NOT_DATA)           >= ERR_NOT_DATA)
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
        sprintf (str, "ERROR! incorrect leftCanaryData = [0x%p]\n", stk->leftCanary);
        strcat (errStr, str);
    }
    if (stk->err % (2 * ERR_RIGHT_CANARY_DATA)  >= ERR_RIGHT_CANARY_DATA)
    {
        sprintf (str, "ERROR! incorrect rightCanaryData = [0x%p]\n", stk->rightCanary);
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

    fprintf (stderr, "%s", errStr);

    return errStr;

    /*
    char errStr[500] = "Error from ";    ///////
    // sprintf
    if (stk->err % (2 * ERR_NOT_DATA)           >= ERR_NOT_DATA)
        strcat (errStr, "ERROR! incorrect *data\n");
    if (stk->err % (2 * ERR_INCORRECT_SIZE)     >= ERR_INCORRECT_SIZE)
        strcat (errStr, "ERROR! incorrect size\n");
    if (stk->err % (2 * ERR_INCORRECT_CAPACITY) >= ERR_INCORRECT_CAPACITY)
        strcat (errStr, "ERROR! incorrect capacity\n");
    if (stk->err % (2 * ERR_LEFT_CANARY)        >= ERR_LEFT_CANARY)
        strcat (errStr, "ERROR! incorrect leftCanary\n");
    if (stk->err % (2 * ERR_RIGHT_CANARY)       >= ERR_RIGHT_CANARY)
        strcat (errStr, "ERROR! incorrect rightCanary\n");
    if (stk->err % (2 * ERR_HASH_STACK)         >= ERR_HASH_STACK)
        strcat (errStr, "ERROR! incorrect hashStack\n");
    if (stk->err % (2 * ERR_HASH_DATA)          >= ERR_HASH_DATA)
        strcat (errStr, "ERROR! incorrect hashStack\n");

    strcat (errStr, "\n");

    printf ("%s", errStr);

    StackDump (stk);

    return errStr;    */

    /*
    printf ("\n\nError from %-3d %s\n", CALL_LINE, CALL_FILE);
    if (stk->err % (2 * ERR_NOT_DATA)           >= ERR_NOT_DATA)
        printf ("ERROR! incorrect *data = %p\n", stk->data);
    if (stk->err % (2 * ERR_INCORRECT_SIZE)     >= ERR_INCORRECT_SIZE)
        printf ("ERROR! incorrect size = %u\n", stk->size);
    if (stk->err % (2 * ERR_INCORRECT_CAPACITY) >= ERR_INCORRECT_CAPACITY)
        printf ("ERROR! incorrect capacity = %u\n", stk->capacity);
    if (stk->err % (2 * ERR_LEFT_CANARY)        >= ERR_LEFT_CANARY)
        printf ("ERROR! incorrect leftCanary = %u\n", stk->leftCanary);
    if (stk->err % (2 * ERR_RIGHT_CANARY)       >= ERR_RIGHT_CANARY)
        printf ("ERROR! incorrect rightCanary = %u\n", stk->rightCanary);
    if (stk->err % (2 * ERR_HASH_STACK)         >= ERR_HASH_STACK)
        printf ("ERROR! incorrect hashStack = %ld\n", stk->hashStack);
    if (stk->err % (2 * ERR_HASH_DATA)          >= ERR_HASH_DATA)
        printf ("ERROR! incorrect hashStack = %ld\n", stk->hashData);
    StackDump (stk);

    */
}
