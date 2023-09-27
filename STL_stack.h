#ifndef STL_stack_
#define STL_stack_

#include "STL_stack_const.h"
#include "STL_stack_struct.h"
#include "error.h"

#define StackCtor(stk)                             \
        if (STL_StackCtor (stk, __FILE__, __LINE__, __func__)) return 0

#define StackCtorCap(stk, capacity)                \
        if (STL_StackCtor (stk, __FILE__, __LINE__, __func__, capacity)) return 0

#define StackDtor(stk)                             \
        if (STL_StackDtor (stk, __FILE__, __LINE__, __func__)) return 0

#define StackPush(stk, value)                      \
        if (STL_StackPush (stk, value, __FILE__, __LINE__, __func__)) return 0

#define StackPop(stk, value)                       \
        if (STL_StackPop  (stk, value, __FILE__, __LINE__, __func__)) return 0

#define STACK_DUMP(stk) STL_StackDump (stk, __FILE__, __LINE__, __func__)
#define STACK_ERR(stk) STL_StackErr (stk, __FILE__, __LINE__, __func__)

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

ErrorType
STL_StackCtor (Stack* stk, const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC,
                           size_t capacity = INITIAL_CAPACITY);

ErrorType
STL_StackDtor (Stack* stk, const char*  CALL_FILE,
                           const size_t CALL_LINE,
                           const char*  CALL_FUNC);

#endif
