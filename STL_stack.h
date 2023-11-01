#ifndef STL_stack_
#define STL_stack_

#include "STL_stack_const.h"
#include "STL_stack_struct.h"
#include "error.h"

#ifdef DEBUG
/// ���������, ��� ������ ������� �� main
#define STL_MSENT_ARGS __FILE__, \
                       __LINE__, \
                       __func__

/// ���������, ��� ������ ������� �� ������� ����������
#define STL_FSENT_ARGS CALL_FILE, \
                       CALL_LINE, \
                       CALL_FUNC

/// ���������, ����������� ���������
#define STL_FREC_ARGS  const char*  CALL_FILE, \
                       const size_t CALL_LINE, \
                       const char*  CALL_FUNC
#endif /* DEBUG */

/**
    \brief ������� ����
    \param stk ��������� �� ����
    \return ��� ������
*/
#ifdef DEBUG
#define StackCtor(stk)                             \
        STL_StackCtor ((stk), #stk, STL_MSENT_ARGS)
#else
#define StackCtor(stk)                             \
        STL_StackCtor ((stk))
#endif

/**
    \brief ������� ���� ��������� �������
    \param stk ��������� �� ����
           capacity ����������� ������ �����
    \return ��� ������
*/
#ifdef DEBUG
#define StackCtorCap(stk, capacity)                \
        STL_StackCtor ((stk), #stk, STL_MSENT_ARGS, capacity)
#else
#define StackCtorCap(stk, capacity)                \
        STL_StackCtor ((stk), capacity)
#endif

/**
    \brief ���������� ����
    \param stk ��������� �� ����
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
    \brief �������� ������� � ����� �����
    \param stk ��������� �� ����
           value �������� ��������
    \return ��� ������
*/
#ifdef DEBUG
#define StackPush(stk, value)                      \
        STL_StackPush ((stk), value, STL_MSENT_ARGS)
#else
#define StackPush(stk, value)                      \
        STL_StackPush ((stk), value)
#endif

/**
    \brief ����� ��������� ������� �� �����
    \param stk ��������� �� ����
           value ��������� �� �������
    \return ��� ������
*/
#ifdef DEBUG
#define StackPop(stk, value)                       \
        STL_StackPop ((stk), value, STL_MSENT_ARGS)
#else
#define StackPop(stk, value)                       \
        STL_StackPop ((stk), value)
#endif

/**
    \brief ������� ����
    \param stk ��������� �� ����
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
    \brief ��������� ���� �� ������������
    \param stk ��������� �� ����
    \return ��� ������
*/
#define ReturnVerificator(stk)                     \
        STL_Verificator ((stk))


ErrorType
STL_StackCtor (STACK* stk

#ifdef DEBUG
               , const char*  CREATE_NAME
               , STL_FREC_ARGS
#endif
               , size_t capacity = INITIAL_CAPACITY);

ErrorType
STL_StackDtor (STACK* stk

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
               );

ErrorType
STL_StackPush (STACK* stk, DataType  value

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
               );
ErrorType
STL_StackPop  (STACK* stk, DataType* value

#ifdef DEBUG
               , STL_FREC_ARGS
#endif
               );
#endif /* STL_stack_ */
