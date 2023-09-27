#ifndef STL_error_
#define STL_error_

#include "STL_stack_const.h"
#include "STL_stack_struct.h"

#ifdef HASH_PROTECTION
    long long
    CountHash (void* data, long long size);
#endif

void
STL_StackDump (const Stack* stk, const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC);

ErrorType
STL_StackErr  (Stack* stk,       const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC);

char*
StackPrintErr (const Stack* stk, const char*  CALL_FILE,
                                 const size_t CALL_LINE,
                                 const char*  CALL_FUNC);

#endif
