#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "error.h"
#include "cdtor.h"
#include "STLstack.h"

//const int DEBAG = 0;
#define $ if (DEBAG)

int main()
{
    struct Stack stk = {};

    if (StackCtor(&stk)) return 0;

    StackDump (&stk, __FILE__, __LINE__);

    if (StackPush (&stk, 7)) return 0;
    $ printf ("Push OK!\n");
    if (StackPush (&stk, 9)) return 0;
    $ printf ("Push OK!\n");
    if (StackPush (&stk, 3)) return 0;
    $ printf ("Push OK!\n");

    int elem = 0;
    if (StackPop (&stk, &elem)) return 0;
    $ printf ("Pop  OK! elem = %d \n", elem);
    if (StackPop (&stk, &elem)) return 0;
    $ printf ("Pop  OK! elem = %d \n", elem);
    if (StackPop (&stk, &elem)) return 0;
    $ printf ("Pop  OK! elem = %d \n", elem);

    StackDump (&stk, __FILE__, __LINE__);

    StackDtor (&stk);

    return 0;
}
