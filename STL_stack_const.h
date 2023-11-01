#ifndef STL_stack_const_
#define STL_stack_const_

#define TOSTR(x) #x

//#define DEBUG
//#define DEBUG_PRINT
#define CANARY_PROTECTION
#define HASH_PROTECTION

/// режим print debug
#ifdef DEBUG_PRINT
    const int DBG = 1;
#else
    const int DEBUG_PRINT = 0;
#endif /* DEBUG_PRINT */

/// debug выводы
#define $ if (DEBUG_PRINT)

/// тип значений стека
#ifndef STACK_T
#define STACK_T char
//#define STACK Stack_char
#endif /* STACK_T */

typedef STACK_T DataType;

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
#define STACK_INCORRECT_DATA '6'
#endif /* STACK_INCORRECT_DATA */

const DataType           INCORRECT_DATA = STACK_INCORRECT_DATA;

/// файл вывода ошибок
#ifndef LOGFILE
#define LOGFILE log.txt
#endif /* LOGFILE */

const char logFile[] = TOSTR(LOGFILE);

#endif
