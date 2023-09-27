#ifndef STL_stack_
#define STL_stack_

#include "STL_stack_const.h"
#include "STL_stack_struct.h"
#include "error.h"

/**
    \brief добавить элемент в конец стека
    \param stk указатель на стек
           value значение элемента
    \return код ошибки
*/
#define StackPush(stk, value)                      \
        if (STL_StackPush ((stk), value, __FILE__, __LINE__, __func__)) return 0

/**
    \brief взять последний элемент из стека
    \param stk указатель на стек
           value указатель на элемент
    \return код ошибки
*/
#define StackPop(stk, value)                       \
        if (STL_StackPop  ((stk), value, __FILE__, __LINE__, __func__)) return 0

/**
    \brief создать стек
    \param stk указатель на стек
    \return код ошибки
*/
#define StackCtor(stk)                             \
        if (STL_StackCtor ((stk), #stk, __FILE__, __LINE__, __func__)) return 0

/**
    \brief создать стек заданного размера
    \param stk указатель на стек
           capacity изначальный размер стека
    \return код ошибки
*/
#define StackCtorCap(stk, capacity)                \
        if (STL_StackCtor ((stk), #stk, __FILE__, __LINE__, __func__, capacity)) return 0

/**
    \brief уничтожить стек
    \param stk указатель на стек
    \return 0
*/
#define StackDtor(stk)                             \
        if (STL_StackDtor ((stk), __FILE__, __LINE__, __func__)) return 0

/**
    \brief вывести стек
    \param stk указатель на стек
    \return void
*/
#define STACK_DUMP(stk) STL_StackDump ((stk), __FILE__, __LINE__, __func__)

/**
    \brief проверка стека на корректность
    \param stk указатель на стек
    \return код ошибки
*/
#define STACK_ERR(stk)  STL_StackErr  ((stk), __FILE__, __LINE__, __func__)

ErrorType
STL_StackPush (Stack* stk, DataType  value,
                           const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC);
ErrorType
STL_StackPop  (Stack* stk, DataType* value,
                           const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC);

ErrorType
STL_StackCtor (Stack* stk, const char*  CREATE_NAME,
                           const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC,
                           size_t capacity = INITIAL_CAPACITY);

ErrorType
STL_StackDtor (Stack* stk, const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC);

#endif
