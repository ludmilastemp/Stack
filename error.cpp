#include "error.h"

void StackDump (const struct Stack* stk, const char* CALL_FILE, const size_t CALL_LINE)
{
    printf ("Stack [%p]\n", stk);       //
    printf ("\t stk    from %-3d %s\n", stk->CREATE_LINE, stk->CREATE_FILE);
    printf ("\t called from %-3d %s\n", CALL_LINE, CALL_FILE);

    printf ("{\n");

    if (!stk)
    {
        return;
    }

    printf ("\t size = %u\n",     stk->size);
    printf ("\t capacity = %u\n", stk->capacity);
    printf ("\t data = [%p]\n",   stk->data);
    printf ("\t {\n");

    size_t i = 0;
    for (; i < stk->size; ++i)
    {
        printf ("\t\t *[%u] = %d\n", i, stk->data[i]);
    }
    for (; i < stk->capacity; ++i)
    {
        printf ("\t\t  [%u] = %d\n", i, stk->data[i]);
    }

    printf ("\t }\n");

    printf ("}\n");
}

int StackErr (struct Stack* stk, const char* CALL_FILE, const size_t CALL_LINE)
{
    int err = 0;
    if (!(stk->data))                  err += ERR_NOT_DATA;
    if (stk->size == INCORRECT_SIZE ||
        stk->size > stk->capacity)     err += ERR_INCORRECT_SIZE;
    if (stk->capacity == 0)            err += ERR_INCORRECT_CAPACITY;

    stk->err = err;

    if (!err) return 0;

    StackPrintErr (stk, CALL_FILE, CALL_LINE);

    return err;
}

void StackPrintErr (const struct Stack* stk, const char* CALL_FILE, const size_t CALL_LINE)
{
    printf ("Error from %-3d %s\n", CALL_LINE, CALL_FILE);
    if (stk->err % (2 * ERR_NOT_DATA)           >= ERR_NOT_DATA)
        printf ("ERROR! incorrect *data = %p\n", stk->data);
    if (stk->err % (2 * ERR_INCORRECT_SIZE)     >= ERR_INCORRECT_SIZE)
        printf ("ERROR! incorrect size = %u\n", stk->size);
    if (stk->err % (2 * ERR_INCORRECT_CAPACITY) >= ERR_INCORRECT_CAPACITY)
        printf ("ERROR! incorrect capacity %u\n", stk->capacity);
    StackDump (stk, CALL_FILE, CALL_LINE);
}
