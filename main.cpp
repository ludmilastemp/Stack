#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "error.h"
#include "cdtor.h"

int main()
{
    struct Stack stk = {};

    if (!StackCtor(&stk)) return 0;
    stk.data[stk.size++] = 5;

    StackDump (&stk, __FILE__, __LINE__);

    StackDtor (&stk);

    return 0;
}

//int Push
