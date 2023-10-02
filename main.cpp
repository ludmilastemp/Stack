#include "STL_stack.h"

int main()
{
    struct Stack stk = { };

    StackCtor (&stk);

    // STACK_DUMP (&stk);

    int elem = 0;

    StackPush (&stk, 7);
    $ printf ("Push OK! elem = %d \n", 7);

    StackPush (&stk, 9);
    $ printf ("Push OK! elem = %d \n", 9);

    stk.size = 6;
    stk.capacity = 0;

    // STACK_DUMP (&stk);

    StackPop (&stk, &elem);
    $ printf ("Pop OK! elem = %d \n", elem);

    // StackDtor (&stk);

    // STACK_DUMP (&stk);

    StackDtor (&stk);

    return 0;
}
