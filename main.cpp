#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "STLstack.h"
#include "error.h"

//#define STACK_ERR(stk) if (STACK_ERR(stk)) return 0;

int main()
{
    int* a = (int*) calloc (7, 1);

    ((char*)a)[0] = 1; //01 01 01 01
    ((char*)a)[1] = 1;
    ((char*)a)[2] = 1;

    ((char*)a)[3] = 1; // 4  5  6  7
    ((char*)a)[4] = 1; //01 00 00 00 = 1

    ((char*)a)[3] = 1; // 4  5  6  7
    ((char*)a)[5] = 1; //00 01 00 00 = 256

    printf ("%p\n", a);
    printf ("%p\n", &a[0]);
    printf ("%p\n\n", &a[1]);
    printf ("%d\n", a[0]);
    printf ("%d\n", a[1]);

    free (a);
    //return 0;

    struct Stack stk = { .leftCanary = 0,
                         .CREATE_FILE = __FILE__,
                         .CREATE_LINE = __LINE__,
                         .CREATE_FUNC = __func__};

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


    STACK_ERR (&stk);
    STACK_DUMP (&stk);

    int elem = 0;
    if (StackPop (&stk, &elem)) return 0;
    $ printf ("Pop  OK! elem = %d \n", elem);
    $ STACK_DUMP (&stk);

    if (StackPop (&stk, &elem)) return 0;
    $ printf ("Pop  OK! elem = %d \n", elem);
    $ STACK_DUMP (&stk);

    //if (StackPop (&stk, &elem)) return 0;
    //$ printf ("Pop  OK! elem = %d \n", elem);

    stk.size = 5;
    stk.capacity = 0;

    STACK_ERR  (&stk);
    STACK_DUMP (&stk);

    StackDtor (&stk);

    return 0;
}
