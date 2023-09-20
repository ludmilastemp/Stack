#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "error.h"

int main()
{
    struct Stack stk = {.data = 0, .size = 5, .capacity = 8};
    stk.data = (int*) calloc (stk.capacity, sizeof (int));
    assert (stk.data);

    StackDump (&stk, __FILE__, __LINE__);

    return 0;
}
