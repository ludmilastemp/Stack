#ifndef STL_error_
#define STL_error_

#include "STL_stack_const.h"
#include "STL_stack_struct.h"

#ifdef HASH_PROTECTION
/**
    \brief ��������� ���
    \param data ���������
           size ������ ������������ ������� ������ (� ������)
    \return ���
*/
long long
CountHash (void* data, long long size);
#endif

/**
    \brief ������� ����
    \param stk ��������� �� ����
    \return void
*/
void
STL_StackDump (const Stack* stk, const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC);

/**
    \brief �������� ����� �� ������������
    \param stk ��������� �� ����
    \return ��� ������
*/
ErrorType
STL_Verificator (Stack* stk,     const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC);

/**
    \brief ����������� ������ ������������ �����
    \param stk ��������� �� ����
    \return ��������� �� ������
*/
char*
StackPrintErr (const Stack* stk, const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC);

#endif
