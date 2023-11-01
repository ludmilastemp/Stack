#include "STL_stack.h"

int main()
{
    struct Stack_int  stk_int  = { };
    struct Stack_char stk_char = { };
//
    StackCtor (&stk_int);
    StackCtor (&stk_char);
//
//    int  elem_int  = 0;
//    char elem_char = '0';
//
//    StackPush (&stk_int,  5);
//    StackPush (&stk_char, '5');
//
//    stk_int.capacity = 0;
//
//    StackPop (&stk_int,  &elem_int);
//
//    printf ("int = %d\n", elem_int);
//
//    StackPop (&stk_char, &elem_char);
//
//    StackDtor (&stk_int);
//    StackDtor (&stk_char);

    return 0;
}
