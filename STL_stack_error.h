//#ifndef STL_stack_error_
//#define STL_stack_error_

#ifndef DBG_E

#include <string.h>
#include <stdarg.h>

#endif /* DBG_E */

#include "STL_stack_const.h"
#include "STL_stack_struct.h"

#ifdef STACK_HASH_PROTECTION
#include "STL_hash.h"
#endif

#ifdef STACK_DEBUG
/// ���������, ����������� ���������
#define STL_FREC_ARGS  const char*  CALL_FILE, \
                       const size_t CALL_LINE, \
                       const char*  CALL_FUNC


/// ���������, ��� ������ ������� �� ������� ����������
#define STL_FSENT_ARGS CALL_FILE, \
                       CALL_LINE, \
                       CALL_FUNC
#endif /* STACK_DEBUG */

/**
    \brief ����������� ������ ������������ �����
    \param stk ��������� �� ����
    \return ��������� �� ������
*/
char*
StackPrintErr (const STACK* stk

#ifdef STACK_DEBUG
               , STL_FREC_ARGS
#endif
               );

//#endif /* STL_error_ */
