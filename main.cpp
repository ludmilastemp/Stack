#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "STLstack.h"
#include "error.h"

//#define STACK_ERR(stk) if (STACK_ERR(stk)) return 0;


int main()
{
    struct Stack stk = { .CREATE_FILE = __FILE__, .CREATE_LINE = __LINE__};

    if (StackCtor (&stk)) return 0;

    STACK_DUMP(&stk);

    if (StackPush (&stk, 7)) return 0;
    $ printf ("Push OK! elem = %d \n", 7);
    if (StackPush (&stk, 9)) return 0;
    $ printf ("Push OK! elem = %d \n", 9);
    if (StackPush (&stk, 3)) return 0;
    $ printf ("Push OK! elem = %d \n", 3);

    STACK_ERR(&stk);
    STACK_DUMP(&stk);

    int elem = 0;
    if (StackPop (&stk, &elem)) return 0;
    $ printf ("Pop  OK! elem = %d \n", elem);
    if (StackPop (&stk, &elem)) return 0;
    $ printf ("Pop  OK! elem = %d \n", elem);
    //if (StackPop (&stk, &elem)) return 0;
    //$ printf ("Pop  OK! elem = %d \n", elem);

    //stk.size = 5;
    //stk.capacity = 0;

    STACK_ERR(&stk);
    STACK_DUMP(&stk);


    StackDtor (&stk);

    return 0;
}
