#ifndef STL_error_
#define STL_error_

#include "STL_stack.h"

long long CountHash (char* data, long long size);

void STL_StackDump (const struct Stack* stk, const char*  CALL_FILE,
                                         const size_t CALL_LINE,
                                         const char*  CALL_FUNC);

int  STL_StackErr  (struct Stack* stk, const char*  CALL_FILE,
                                   const size_t CALL_LINE,
                                   const char*  CALL_FUNC);

char* StackPrintErr (const struct Stack* stk, const char*  CALL_FILE,
                                              const size_t CALL_LINE,
                                              const char*  CALL_FUNC);

#endif
