#include "STLstack.h"

int StackCtor (Stack* stk, size_t capacity)
{
    if (!stk)
    {
        return 1;
    }

    stk->size     = 0;
    stk->capacity = capacity;
    stk->err      = 0;

    stk->data     = (DataType*) calloc (stk->capacity * sizeof (DataType) +
                                        2 * sizeof (CanaryType), sizeof (char));

    if (!stk->data)
    {
        stk->err = ERR_NOT_MEMORY;
        return stk->err;
    }

    stk->data = (DataType*) ((char*)stk->data + sizeof (CanaryType));

    *((CanaryType*)stk->data - 1) = (CanaryType) (stk->data);
    *(CanaryType*) (stk->data + stk->capacity) = (CanaryType) (stk->data);

    stk->leftCanary  = (CanaryType) (stk);
    stk->rightCanary = (CanaryType) (stk);
    stk->rightCanary = stk->leftCanary;

    printf ("Ctor: %p %p\n", &stk->leftCanary, &stk->rightCanary);
    printf ("Ctor: %p %p\n", stk->leftCanary, stk->rightCanary);

    stk->hashStack = CountHash ((char*) stk, sizeof (Stack));

    for (size_t i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = INCORRECT_DATA;
    }

    stk->hashData = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);

    return STACK_ERR (stk);
}

int StackDtor (Stack* stk)
{
    if (STACK_ERR (stk)) return stk->err;

    stk->size        = INCORRECT_SIZE;
    stk->capacity    = 0;
    stk->data = (DataType*)((CanaryType*)(stk->data) - 1);
    free(stk->data);
    stk->data        = nullptr;
    stk->err         = 0;
    stk->leftCanary  = 0;
    stk->rightCanary = 0;
    stk->hashStack   = 0;
    stk->hashData    = 0;

    return 0;
}
