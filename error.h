#ifndef STL_error_
#define STL_error_

struct Stack
{
    int* data;
    size_t size;
    size_t capacity;
    int err;
};

int  StackErr (const struct Stack* stk);

void StackPrintErr (const int err);

void StackDump (const struct Stack* stk, const char* FILE, const size_t LINE);

void StackDump (const struct Stack* stk, const char* FILE, const size_t LINE)
{
    printf ("Stack [%p]\n", stk);
    printf ("\t called from %s %d\n", FILE, LINE);

    printf ("{\n");

    if (!stk)
    {
        return;
    }

    printf ("\t size = %u\n",     stk->size);
    printf ("\t capacity = %u\n", stk->capacity);
    printf ("\t data = [%p]\n",    stk->data);
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

int StackErr (struct Stack* stk)
{
    int err = 0;
    if (! (stk->data))         err += 1;
    if (! (stk->size >= 0))    err += 2;
    if (! (stk->capacity > 0)) err += 4;

    stk->err = err;

    StackPrintErr (err);

    return err;
}

void StackPrintErr (const int err)
{
    if (!err) return;

    //printf ("\t called from %s %d\n", FILE, LINE);

    if (err % 2 >= 1) printf ("incorrect *data\n");
    if (err % 4 >= 2) printf ("incorrect size\n");
    if (err % 8 >= 4) printf ("incorrect capacity\n");
}

#endif
