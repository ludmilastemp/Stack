#ifndef STL_stack_
#define STL_stack_

#include "STL_stack_const.h"
#include "STL_stack_struct.h"
#include "error.h"

#ifdef DEBUG
/// аргументы, при вызове функций из main
#define STL_MSENT_ARGS __FILE__, \
                       __LINE__, \
                       __func__

/// аргументы, при вызове функций из функции библиотеки
#define STL_FSENT_ARGS CALL_FILE, \
                       CALL_LINE, \
                       CALL_FUNC

/// аргументы, принимаемые функциями
#define STL_FREC_ARGS  const char*  CALL_FILE, \
                       const size_t CALL_LINE, \
                       const char*  CALL_FUNC
#endif /* DEBUG */

/**
    \brief создать стек
    \param stk указатель на стек
    \return код ошибки
*/
#ifdef DEBUG
#define StackCtor(stk)                             \
        STL_StackCtor ((stk), #stk, STL_MSENT_ARGS)
#else
#define StackCtor(stk)                             \
        STL_StackCtor ((stk))
#endif

/**
    \brief создать стек заданного размера
    \param stk указатель на стек
           capacity изначальный размер стека
    \return код ошибки
*/
#ifdef DEBUG
#define StackCtorCap(stk, capacity)                \
        STL_StackCtor ((stk), #stk, STL_MSENT_ARGS, capacity)
#else
#define StackCtorCap(stk, capacity)                \
        STL_StackCtor ((stk), capacity)
#endif

/**
    \brief уничтожить стек
    \param stk указатель на стек
    \return 0
*/
#ifdef DEBUG
#define StackDtor(stk)                             \
        STL_StackDtor ((stk), STL_MSENT_ARGS)
#else
#define StackDtor(stk)                             \
        STL_StackDtor ((stk))
#endif

/**
    \brief добавить элемент в конец стека
    \param stk указатель на стек
           value значение элемента
    \return код ошибки
*/
#ifdef DEBUG
#define StackPush(stk, value)                      \
        STL_StackPush ((stk), value, STL_MSENT_ARGS)
#else
#define StackPush(stk, value)                      \
        STL_StackPush ((stk), value)
#endif

/**
    \brief взять последний элемент из стека
    \param stk указатель на стек
           value указатель на элемент
    \return код ошибки
*/
#ifdef DEBUG
#define StackPop(stk, value)                       \
        STL_StackPop  ((stk), value, STL_MSENT_ARGS)
#else
#define StackPop(stk, value)                       \
        STL_StackPop  ((stk), value)
#endif

/**
    \brief вывести стек
    \param stk указатель на стек
    \return void
*/
#ifdef DEBUG
#define STACK_DUMP(stk)                            \
        STL_StackDump ((stk), STL_MSENT_ARGS)
#else
#define STACK_DUMP(stk)                            \
        STL_StackDump ((stk))
#endif

/**
    \brief проверяет стек на корректность
    \param stk указатель на стек
    \return код ошибки
*/
#define ReturnVerificator(stk)                     \
        STL_Verificator ((stk))


ErrorType
STL_StackCtor (Stack* stk

#ifdef DEBUG
               , const char*  CREATE_NAME
               , STL_FREC_ARGS
#endif
               , size_t capacity = INITIAL_CAPACITY);

ErrorType
STL_StackDtor (Stack* stk

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
               );

ErrorType
STL_StackPush (Stack* stk, DataType  value

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
               );
ErrorType
STL_StackPop  (Stack* stk, DataType* value

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
               );
#endif /* STL_stack_ */
