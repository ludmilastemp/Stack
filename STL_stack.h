//#ifndef STL_stack_
//#define STL_stack_

//#include "STL_stack_const.h"
//#include "STL_stack_struct.h"
#include "STL_stack_error.h"

typedef STACK_T StackDataType;


#ifdef STACK_DEBUG
    /// ���������, ��� ������ ������� �� main
    #define STL_MSENT_ARGS __FILE__,                \
                           __LINE__,                \
                           __func__

    /// ���������, ��� ������ ������� �� ������� ����������
    #define STL_FSENT_ARGS CALL_FILE,               \
                           CALL_LINE,               \
                           CALL_FUNC

    /// ���������, ����������� ���������
    #define STL_FREC_ARGS  const char*  CALL_FILE,  \
                           const size_t CALL_LINE,  \
                           const char*  CALL_FUNC

    /// ���������, ��� ������ � DUMP
    #define STL_DUMP_ARGS stk->CREATE_NAME,         \
                          stk->CREATE_FILE,         \
                          stk->CREATE_LINE,         \
                          stk->CREATE_FUNC
#endif /* STACK_DEBUG */

/**
    \brief ������� ����
    \param stk ��������� �� ����
    \return ��� ������
*/
#ifdef STACK_DEBUG
    #define StackCtor(stk)                                          \
            STL_StackCtor ((stk), #stk, STL_MSENT_ARGS)
#else
    #define StackCtor(stk)                                          \
            STL_StackCtor ((stk))
#endif

/**
    \brief ������� ���� ��������� �������
    \param stk ��������� �� ����
           capacity ����������� ������ �����
    \return ��� ������
*/
#ifdef STACK_DEBUG
    #define StackCtorCap(stk, capacity)                             \
            STL_StackCtor ((stk), #stk, STL_MSENT_ARGS, capacity)
#else
    #define StackCtorCap(stk, capacity)                             \
            STL_StackCtor ((stk), capacity)
#endif

/**
    \brief ���������� ����
    \param stk ��������� �� ����
    \return 0
*/
#ifdef STACK_DEBUG
    #define StackDtor(stk)                                          \
            STL_StackDtor ((stk), STL_MSENT_ARGS)
#else
    #define StackDtor(stk)                                          \
            STL_StackDtor ((stk))
#endif

/**
    \brief �������� ������� � ����� �����
    \param stk ��������� �� ����
           value �������� ��������
    \return ��� ������
*/
#ifdef STACK_DEBUG
    #define StackPush(stk, value)                                   \
            do {                                                    \
                if (STL_StackPush ((stk), value, STL_MSENT_ARGS))   \
                {                                                   \
                    StackPrintErr (stk, STL_MSENT_ARGS);            \
                    StackDump (stk);                                \
                }                                                   \
            } while (false)
#else
    #define StackPush(stk, value)                                   \
            do {                                                    \
                if (STL_StackPush ((stk), value))                   \
                {                                                   \
                    StackPrintErr (stk);                            \
                    StackDump (stk);                                \
                }                                                   \
            } while (false)
#endif

/**
    \brief ����� ��������� ������� �� �����
    \param stk ��������� �� ����
           value ��������� �� �������
    \return ��� ������
*/
#ifdef STACK_DEBUG
    #define StackPop(stk, value)                                    \
            do {                                                    \
                if (STL_StackPop ((stk), value, STL_MSENT_ARGS))    \
                {                                                   \
                    StackPrintErr (stk, STL_MSENT_ARGS);            \
                    StackDump (stk);                                \
                }                                                   \
            } while (false)
#else
    #define StackPop(stk, value)                                    \
            do {                                                    \
                if (STL_StackPop ((stk), value))                    \
                {                                                   \
                    StackPrintErr (stk);                            \
                    StackDump (stk);                                \
                }                                                   \
            } while (false)
#endif

/**
    \brief ��������� ���� �� ������������ � ������� ���� � ������ ������
    \param stk ��������� �� ����
    \return ��� ������
*/
#ifdef STACK_DEBUG
    #define StackVerificator(stk)                                   \
    do {                                                            \
                                                                    \
        if (STL_StackVerificator ((stk)))                           \
        {                                                           \
            StackPrintErr (stk, STL_MSENT_ARGS);                    \
            StackDump (stk);                                        \
        }                                                           \
    } while (false)
#else
    #define StackVerificator(stk)                                   \
    do {                                                            \
                                                                    \
        if (STL_StackVerificator ((stk)))                           \
        {                                                           \
            StackPrintErr (stk);                                    \
            StackDump (stk);                                        \
        }                                                           \
    } while (false)
#endif

/**
    \brief ������� ����
    \param stk ��������� �� ����
    \return void
*/
#ifdef STACK_DEBUG
    #define StackDump(stk)                                          \
        STL_StackDump ((stk), STL_MSENT_ARGS);
#else
    #define StackDump(stk)                                          \
        STL_StackDump ((stk));
#endif

StackErrorType
STL_StackCtor (STACK* stk

#ifdef STACK_DEBUG
               , const char*  CREATE_NAME
               , STL_FREC_ARGS
#endif
               , size_t capacity = INITIAL_CAPACITY);

StackErrorType
STL_StackDtor (STACK* stk

#ifdef STACK_DEBUG
               , STL_FREC_ARGS
#endif
               );

StackErrorType
STL_StackPush (STACK* stk, StackDataType  value

#ifdef STACK_DEBUG
               , STL_FREC_ARGS
#endif
               );
StackErrorType
STL_StackPop  (STACK* stk, StackDataType* value

#ifdef STACK_DEBUG
               , STL_FREC_ARGS
#endif
               );

/**
    \brief �������� ����� �� ������������
    \param stk ��������� �� ����
    \return ��� ������
*/
StackErrorType
STL_StackVerificator (STACK* stk);

void
STL_StackDump (const STACK* stk

#ifdef STACK_DEBUG
               , STL_FREC_ARGS
#endif
               );
//#endif /* STL_stack_ */
