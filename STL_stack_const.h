#ifndef STL_stack_const_
#define STL_stack_const_

#include "STL_stack_const_int.h"

#define TOSTR(x) #x

//#define STACK_DEBUG
//#define STACK_DEBUG_PRINT
//#define STACK_CANARY_PROTECTION
//#define STACK_HASH_PROTECTION

/// режим print debug
#ifdef STACK_DEBUG_PRINT
    const int STACK_DEBUG_PRINT_V = 1;
#else
    const int STACK_DEBUG_PRINT_V = 0;
#endif /* STACK_DEBUG_PRINT */

/// debug выводы
#define $ if (STACK_DEBUG_PRINT_V)

/// спецификатор формата типа стека
#ifndef STACK_DATA_PRINT_SPECIFIER
#define STACK_DATA_PRINT_SPECIFIER TOSTR(%d)
#endif /* STACK_DATA_PRINT_SPECIFIER */

/// размер стека при создании
#ifndef STACK_INITIAL_CAPACITY
#define STACK_INITIAL_CAPACITY 1
#endif /* STACK_INITIAL_CAPACITY */

const unsigned long long INITIAL_CAPACITY  = STACK_INITIAL_CAPACITY;

/// коэффициент увеличения/уменьшения стека
#ifndef STACK_EXPAND_MULTIPLIER
#define STACK_EXPAND_MULTIPLIER 2
#endif /* STACK_EXPAND_MULTIPLIER */

const unsigned long long EXPAND_MULTIPLIER = STACK_EXPAND_MULTIPLIER;

/// неккоректный размер стека
#ifndef STACK_INCORRECT_CAPACITY
#define STACK_INCORRECT_CAPACITY -1u
#endif /* STACK_INCORRECT_CAPACITY */

const unsigned long long INCORRECT_CAPACITY = STACK_INCORRECT_CAPACITY;

/// некорректное количество элементов стека
#ifndef STACK_INCORRECT_SIZE
#define STACK_INCORRECT_SIZE -1u
#endif /* STACK_EXPAND_MULTIPLIER */

const unsigned long long INCORRECT_SIZE = STACK_INCORRECT_SIZE;

/// неккоректное значение элементов стека
#ifndef STACK_INCORRECT_DATA
#define STACK_INCORRECT_DATA 666
#endif /* STACK_INCORRECT_DATA */

const StackDataType      INCORRECT_DATA = STACK_INCORRECT_DATA;

/// файл вывода ошибок
#ifndef LOGFILE
#define LOGFILE log.txt
#endif /* LOGFILE */

const char logFile[] = TOSTR(LOGFILE);

#endif
