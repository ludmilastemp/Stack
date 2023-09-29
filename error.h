#ifndef STL_error_
#define STL_error_

#include "STL_stack_const.h"
#include "STL_stack_struct.h"

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
STL_Verificator (Stack* stk,     const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC);

/**
    \brief вывести стек
    \param stk указатель на стек
    \return void
*/
void
STL_StackDump (const Stack* stk, const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC);

/**
    \brief расшифровка ошибок корректности стека
    \param stk указатель на стек
    \return указатель на строку
*/
char*
StackPrintErr (const Stack* stk, const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC);

#endif
