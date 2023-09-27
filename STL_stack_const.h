#ifndef STL_stack_const_
#define STL_stack_const_

/// режим debug
const int DEBUG = 0;
#define $ if (DEBUG)                   // $printf()

/// тип значений стека
#ifndef STACK_T
#define STACK_T int
#endif /* STACK_T */

typedef STACK_T DataType;

/// спецификатор формата типа стека
#ifndef PRINT_DATA
#define PRINT_DATA "%d"
#endif /* PRINT_DATA */

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
#define STACK_INCORRECT_CAPACITY 0
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

const DataType           INCORRECT_DATA = STACK_INCORRECT_DATA;

/// файл вывода ошибок
const char logFile[] = "log.txt";

#endif
