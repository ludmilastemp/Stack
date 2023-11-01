#ifndef STL_error_
#define STL_error_

#include "STL_stack_const.h"
#include "STL_stack_struct.h"
#ifdef HASH_PROTECTION
#include "hash.h"
#endif

#ifdef DEBUG
/// аргументы, принимаемые функциями
#define STL_FREC_ARGS  const char*  CALL_FILE, \
                       const size_t CALL_LINE, \
                       const char*  CALL_FUNC


/// аргументы, при вызове функций из функции библиотеки
#define STL_FSENT_ARGS CALL_FILE, \
                       CALL_LINE, \
                       CALL_FUNC


/// аргументы, при вызове функций из функции библиотеки
#define STL_DUMP_ARGS stk->CREATE_NAME, \
                      stk->CREATE_FILE, \
                      stk->CREATE_LINE, \
                      stk->CREATE_FUNC
#endif /* DEBUG */

/**
    \brief проверка стека на корректность
    \param stk указатель на стек
    \return код ошибки
*/
ErrorType
STL_Verificator (STACK* stk);

/**
    \brief вывести стек
    \param stk указатель на стек
    \return void
*/
void
STL_StackDump (const STACK* stk

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
               );

/**
    \brief расшифровка ошибок корректности стека
    \param stk указатель на стек
    \return указатель на строку
*/
char*
StackPrintErr (const STACK* stk

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
               );

#endif /* STL_error_ */
