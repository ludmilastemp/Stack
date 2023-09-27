#include "STL_stack.h"
                                                      //������������


int main()
{
    struct Stack stk = {
#ifdef CANARY_PROTECTION
                         .leftCanary = 0,
#endif
                         .CREATE_FILE = __FILE__,
                         .CREATE_LINE = __LINE__,
                         .CREATE_FUNC = __func__};

    //FILE* fp = fopen ("log.txt", "r")

    StackCtor (&stk);

    //STACK_DUMP (&stk);

    int elem = 0;

    StackPush (&stk, 7);
    $ printf ("Push OK! elem = %d \n", 7);
    $ STACK_DUMP (&stk);
                          //*
    StackPush (&stk, 9);
    $ printf ("Push OK! elem = %d \n", 9);
    $ STACK_DUMP (&stk);

    StackPush (&stk, 3);
    $ printf ("Push OK! elem = %d \n", 3);
    $ STACK_DUMP (&stk);

    StackPush (&stk, 1);
    $    STACK_DUMP (&stk);
    StackPush (&stk, 2);
    $    STACK_DUMP (&stk);
    StackPush (&stk, 3);
    $    STACK_DUMP (&stk);
    StackPop (&stk, &elem);
    $    STACK_DUMP (&stk);
    StackPop (&stk, &elem);
    $    STACK_DUMP (&stk);
    StackPop (&stk, &elem);
    $    STACK_DUMP (&stk);



    $ STACK_DUMP (&stk);

    StackPop (&stk, &elem);
    $ printf ("Pop  OK! elem = %d \n", elem);
    $ STACK_DUMP (&stk);

    StackPop (&stk, &elem);
    $ printf ("Pop  OK! elem = %d \n", elem);
    $ STACK_DUMP (&stk);

    //*
    StackPush (&stk, 1);
    $    STACK_DUMP (&stk);

    StackPop (&stk, &elem);
    StackPop (&stk, &elem);
    StackPop (&stk, &elem);
    StackPop (&stk, &elem);
    StackPop (&stk, &elem);
    StackPop (&stk, &elem);
    StackPop (&stk, &elem);
    StackPop (&stk, &elem);
    StackPop (&stk, &elem);  //*/


    stk.size = 6;
    stk.capacity = 0;

    //StackPop (&stk, &elem);
    //$ printf ("Pop  OK! elem = %d \n", elem);

    //STACK_ERR  (&stk);  */
    $ STACK_DUMP (&stk);

    StackDtor (&stk);

    return 0;
}
