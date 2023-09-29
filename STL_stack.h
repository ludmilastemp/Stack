#ifndef STL_stack_
#define STL_stack_

#include "STL_stack_const.h"
#include "STL_stack_struct.h"
#include "error.h"

/**
    \brief ������� ����
    \param stk ��������� �� ����
    \return ��� ������
*/
#define StackCtor(stk)                             \
        if (STL_StackCtor ((stk), #stk, __FILE__, __LINE__, __func__)) return 0

/**
    \brief ������� ���� ��������� �������
    \param stk ��������� �� ����
           capacity ����������� ������ �����
    \return ��� ������
*/
#define StackCtorCap(stk, capacity)                \
        if (STL_StackCtor ((stk), #stk, __FILE__, __LINE__, __func__, capacity)) return 0

/**
    \brief ���������� ����
    \param stk ��������� �� ����
    \return 0
*/
#define StackDtor(stk)                             \
        if (STL_StackDtor ((stk), __FILE__, __LINE__, __func__)) return 0

/**
    \brief �������� ������� � ����� �����
    \param stk ��������� �� ����
           value �������� ��������
    \return ��� ������
*/
#define StackPush(stk, value)                      \
        if (STL_StackPush ((stk), value, __FILE__, __LINE__, __func__)) return 0

/**
    \brief ����� ��������� ������� �� �����
    \param stk ��������� �� ����
           value ��������� �� �������
    \return ��� ������
*/
#define StackPop(stk, value)                       \
        if (STL_StackPop  ((stk), value, __FILE__, __LINE__, __func__)) return 0

/**
    \brief ��������� ���� �� ������������ � ������� ���� � ������ ������
    \param stk ��������� �� ����
    \return ��� ������
*/
#define Verificator(stk)                                       \
do {                                                           \
                                                               \
    if (STL_Verificator ((stk), __FILE__, __LINE__, __func__)) \
    {                                                          \
        StackPrintErr (stk, CALL_FILE, CALL_LINE, CALL_FUNC);  \
        STL_StackDump ((stk), CALL_FILE, CALL_LINE, CALL_FUNC);   \
        return stk->err;                                       \
    }                                                          \
} while (false)

/**
    \brief ������� ����
    \param stk ��������� �� ����
    \return void
*/
#define STACK_DUMP(stk) STL_StackDump ((stk), __FILE__, __LINE__, __func__)

/**
    \brief ��������� ���� �� ������������
    \param stk ��������� �� ����
    \return ��� ������
*/
#define ReturnVerificator(stk) STL_Verificator ((stk), __FILE__, __LINE__, __func__)

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
#endif
