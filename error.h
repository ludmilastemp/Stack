#ifndef STL_error_
#define STL_error_

#include "STL_stack_const.h"
#include "STL_stack_struct.h"

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

#ifdef HASH_PROTECTION
/**
    \brief посчитать хеш
    \param data указатель
           size размер проверяемого отрезка памяти (в байтах)
    \return хеш
*/
long long
CountHash (void* data, long long size);
#endif

/**
    \brief проверка стека на корректность
    \param stk указатель на стек
    \return код ошибки
*/
ErrorType
STL_Verificator (Stack* stk);

/**
    \brief вывести стек
    \param stk указатель на стек
    \return void
*/
void
STL_StackDump (const Stack* stk

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
StackPrintErr (const Stack* stk

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
               );

#endif /* STL_error_ */
