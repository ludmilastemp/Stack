#ifndef DBG_E

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* DBG_E */

#include "STL_stack.h"
#include "error.h"

#define StackCtor(stk)                             \
        STL_StackCtor (stk, __FILE__, __LINE__, __func__)

#define StackDtor(stk)                             \
        STL_StackDtor (stk, __FILE__, __LINE__, __func__)

#define StackPush(stk, value)                      \
        STL_StackPush (stk, value, __FILE__, __LINE__, __func__)

#define StackPop(stk, value)                       \
        STL_StackPop  (stk, value, __FILE__, __LINE__, __func__)

#define STACK_DUMP(stk) STL_StackDump (stk, __FILE__, __LINE__, __func__)
#define STACK_ERR(stk) STL_StackErr (stk, __FILE__, __LINE__, __func__)

int main()
{
    struct Stack stk = { .leftCanary = 0,
                         .CREATE_FILE = __FILE__,
                         .CREATE_LINE = __LINE__,
                         .CREATE_FUNC = __func__ };

    if (StackCtor (&stk)) return 0;

    STACK_DUMP (&stk);

    if (StackPush (&stk, 7)) return 0;
    $ printf ("Push OK! elem = %d \n", 7);
    $ STACK_DUMP (&stk);

    if (StackPush (&stk, 9)) return 0;
    $ printf ("Push OK! elem = %d \n", 9);
    $ STACK_DUMP (&stk);

    if (StackPush (&stk, 3)) return 0;
    $ printf ("Push OK! elem = %d \n", 3);
    $ STACK_DUMP (&stk);


    //STACK_ERR (&stk);
    STACK_DUMP (&stk);

    int elem = 0;
    if (StackPop (&stk, &elem)) return 0;
    $ printf ("Pop  OK! elem = %d \n", elem);
    $ STACK_DUMP (&stk);

    if (StackPop (&stk, &elem)) return 0;
    $ printf ("Pop  OK! elem = %d \n", elem);
    $ STACK_DUMP (&stk);

    stk.size = 6;
    stk.capacity = 0;

    if (StackPop (&stk, &elem)) return 0;
    $ printf ("Pop  OK! elem = %d \n", elem);

    //STACK_ERR  (&stk);
    STACK_DUMP (&stk);

    StackDtor (&stk);

    return 0;
}
