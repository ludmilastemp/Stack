#include "error.h"

#include <string.h>

long long CountHash (char* data, long long size)
{
    long long hash = 0;

    printf ("I CountHash: *data = [%p], size = %d\n", data, size);

    for (size_t i = 0; i < size; ++i)
    {
        hash += data[i];
    }

    printf ("hash = %ld\n", hash);

    return hash;
}

void StackDump (const struct Stack* stk, const char*  CALL_FILE,
                                         const size_t CALL_LINE,
                                         const char*  CALL_FUNC)
{
    printf ("\nStack [%p]\n", stk);       //
    printf ("\t stk    from %-3d %s %s\n", stk->CREATE_LINE,
                                           stk->CREATE_FILE,
                                           stk->CREATE_FUNC);
    printf ("\t called from %-3d %s %s\n", CALL_LINE,
                                           CALL_FILE,
                                           CALL_FUNC);
    printf ("{\n");

    if (!stk)
    {
        return;
    }

    printf ("\t leftCanary = [%8p]   rightCanary = [%8p]\n", stk->leftCanary,
                                                             stk->rightCanary);
    printf ("\t leftCanary = [%8p]   rightCanary = [%8p]\n", stk,
                                                             stk);
    printf ("\t size = %u\n",     stk->size);
    printf ("\t capacity = %u\n", stk->capacity);
    printf ("\t data = [%p]\n",   stk->data);
    printf ("\t {\n");

    if (!stk->data)
    {
        return;
    }

    size_t i = 0;
    for (; i < stk->size; ++i)
    {
        if (stk->data[i] == INCORRECT_DATA)
            printf ("\t\t *[%u] = POISON\n", i);
        else
            printf ("\t\t *[%u] = " PRINT_DATA "\n", i, stk->data[i]);
    }
    for (; i < stk->capacity; ++i)
    {
        if (stk->data[i] == INCORRECT_DATA)
            printf ("\t\t  [%u] = POISON\n", i);
        else
            printf ("\t\t  [%u] = " PRINT_DATA "\n", i, stk->data[i]);
    }

    printf ("\t }\n");

    printf ("\t hashStack = %ld\n", stk->hashStack);
    printf ("\t hashData  = %ld\n", stk->hashData);

    printf ("}\n");
}

int StackErr (struct Stack* stk, const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC)
{
    int err = 0;
    if (!(stk->data))                  err += ERR_NOT_DATA;
    if (stk->size == INCORRECT_SIZE ||
        stk->size > stk->capacity)     err += ERR_INCORRECT_SIZE;
    if (stk->capacity == 0)                         err += ERR_INCORRECT_CAPACITY;
    if (stk->leftCanary != (CanaryType) stk)        err += ERR_LEFT_CANARY;
    //if (rightCanary != stk)            err += ERR_RIGHT_CANARY;

    long long hashStackRef = stk->hashStack;
    long long hashDataRef  = stk->hashData;

    stk->hashStack = 0;
    stk->hashData  = 0;

    stk->hashStack = CountHash ((char*) stk, sizeof (Stack));
    stk->hashData  = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);

    //if (stk->hashStack != hashStackRef) err += ERR_HASH_STACK;
    //if (stk->hashData  != hashDataRef)  err += ERR_HASH_DATA;

    stk->err = err;

    if (!err) return 0;

    StackPrintErr (stk, CALL_FILE, CALL_LINE, CALL_FUNC);

    return err;
}

char* StackPrintErr (const struct Stack* stk, const char*  CALL_FILE,
                                              const size_t CALL_LINE,
                                              const char*  CALL_FUNC)
{
    /*
    char errStr[200] = "Error from ";    ///////
    strcat (errStr, CALL_FILE);

    if (stk->err % (2 * ERR_NOT_DATA)           >= ERR_NOT_DATA)
    {
        strcat (errStr, "\nERROR! incorrect *data = ");
        //strcat (errStr, %p, stk->data);
    }
    if (stk->err % (2 * ERR_INCORRECT_SIZE)     >= ERR_INCORRECT_SIZE)
    {
        strcat (errStr,"\nERROR! incorrect size = ");
        //strcat (errStr,"%u", stk->size);
    }
    if (stk->err % (2 * ERR_INCORRECT_CAPACITY) >= ERR_INCORRECT_CAPACITY)
    {
        strcat (errStr,"\nERROR! incorrect capacity = ");
        //strcat (errStr,"%u", stk->capacity);
    }
    strcat (errStr, "\n\0");

    printf ("%s", errStr);

    //return errStr;     */

    //*
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
    StackDump (stk, CALL_FILE, CALL_LINE, CALL_FUNC);

    //*/
}
