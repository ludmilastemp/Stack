#include "STL_stack_const_int.h"
#include "STL_stack.h"

int main ()
{
    Stack_int stki = { };
    int a = 0;

    StackCtor (&stki);

    StackPush (&stki, 57);
    StackPush (&stki, 68);
    StackPush (&stki, 79);

    StackPop (&stki, &a);

    StackDump (&stki);

    StackDtor (&stki);
}
