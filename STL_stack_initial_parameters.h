#ifndef STL_stack_initial_parameters_
#define STL_stack_initial_parameters_

#define CONCAT(arg1, arg2) arg1##arg2
#define STACK_TYPED_WITH(type) CONCAT (Stack_, type)
#define STACK STACK_TYPED_WITH(STACK_T)

/// ����� print debug
#ifdef STACK_DEBUG_PRINT
    const int STACK_DEBUG_PRINT_V = 1;
#else
    const int STACK_DEBUG_PRINT_V = 0;
#endif /* STACK_DEBUG_PRINT */

#define TOSTR(x) #x

/// ������������ ������� ���� �����
#ifndef STACK_DATA_PRINT_SPECIFIER
#define STACK_DATA_PRINT_SPECIFIER TOSTR(%d)
#endif /* STACK_DATA_PRINT_SPECIFIER */

/// ������ ����� ��� ��������
#ifndef STACK_INITIAL_CAPACITY
#define STACK_INITIAL_CAPACITY 1
#endif /* STACK_INITIAL_CAPACITY */

const unsigned long long INITIAL_CAPACITY  = STACK_INITIAL_CAPACITY;

/// ����������� ����������/���������� �����
#ifndef STACK_EXPAND_MULTIPLIER
#define STACK_EXPAND_MULTIPLIER 2
#endif /* STACK_EXPAND_MULTIPLIER */

const unsigned long long EXPAND_MULTIPLIER = STACK_EXPAND_MULTIPLIER;

/// ������������ ������ �����
#ifndef STACK_INCORRECT_CAPACITY
#define STACK_INCORRECT_CAPACITY -1u
#endif /* STACK_INCORRECT_CAPACITY */

const unsigned long long INCORRECT_CAPACITY = STACK_INCORRECT_CAPACITY;

/// ������������ ���������� ��������� �����
#ifndef STACK_INCORRECT_SIZE
#define STACK_INCORRECT_SIZE -1u
#endif /* STACK_EXPAND_MULTIPLIER */

const unsigned long long INCORRECT_SIZE = STACK_INCORRECT_SIZE;

/// ������������ �������� ��������� �����
#ifndef STACK_INCORRECT_DATA
#define STACK_INCORRECT_DATA {0}
#endif /* STACK_INCORRECT_DATA */

const STACK_T            INCORRECT_DATA = STACK_INCORRECT_DATA;

/// ���� ������ ������
#ifndef LOGFILE
#define LOGFILE log.txt
#endif /* LOGFILE */

const char logFile[] = TOSTR(LOGFILE);

#endif /* STL_stack_initial_parameters_ */
