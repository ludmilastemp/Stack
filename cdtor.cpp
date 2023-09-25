#include "STL_stack.h"

int STL_StackCtor (Stack* stk, const char*  CALL_FILE,
                               const size_t CALL_LINE,
                               const char*  CALL_FUNC,
                               size_t capacity)
{
    if (!stk)
    {
        return 1; // WHo?     // assert
    }

    stk->size     = 0;
    stk->capacity = capacity;
    stk->err      = 0;

    stk->data     = (DataType*) calloc (stk->capacity * sizeof (DataType) +
                                        2 * sizeof (CanaryType), sizeof (char)); // Layout [CA][][]
    // StackReallocUp()
    if (!stk->data)
    {
        stk->err = ERR_NOT_MEMORY;
        return stk->err;
    }

    stk->data = (DataType*) ((CanaryType*)stk->data + 1);

    *((CanaryType*)stk->data - 1) = (CanaryType) (stk->data);
    *(CanaryType*) (stk->data + stk->capacity) = (CanaryType) (stk->data);

    stk->leftCanary  = (CanaryType) (stk);
    stk->rightCanary = (CanaryType) (stk);

    stk->hashStack = CountHash ((char*) stk, sizeof (Stack));

    for (size_t i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = INCORRECT_DATA; // pointer != poison
    }

    stk->hashData = CountHash ((char*) stk->data, sizeof (DataType) * stk->capacity);

    return StackErr (stk);
}

int STL_StackDtor (Stack* stk, const char*  CALL_FILE,
                               const size_t CALL_LINE,
                               const char*  CALL_FUNC)
{
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
