
#include "STACK_FILE_TYPE_int.h"
#include "generic.h"

#include "STACK_FILE_TYPE_char.h"
#include "generic.h"

#include "STACK_FILE_TYPE_my.h"
#include "generic.h"

//struct MY
//{
//    int xax;
//    int xex;
//};

int main ()
{
    Stack_MY  stk_my = { };
    StackCtor (&stk_my);

    MY cat1 = {5, 12};
    MY cat2 = {3, 1};
    MY cat3 = {89, 10};

    StackPush (&stk_my, cat1);
    StackPush (&stk_my, cat2);
    StackPush (&stk_my, cat3);
    StackDump (&stk_my);

    printf ("%d\n", stk_my.data[2].xex);

    int temp_int = 0;
    Stack_int stk_int = { };
    StackCtor (&stk_int);
    StackPush (&stk_int, 57);
    StackPush (&stk_int, 68);
    StackPush (&stk_int, 79);
    StackPop  (&stk_int, &temp_int);
    StackDump (&stk_int);
    StackDtor (&stk_int);

    char temp_char = 0;
    Stack_char stk_char = { };
    StackCtor (&stk_char);
    StackPush (&stk_char, '5');
    StackPush (&stk_char, '6');
    StackPush (&stk_char, '7');
    StackPop  (&stk_char, &temp_char);
    StackDump (&stk_char);
    StackDtor (&stk_char);
}
