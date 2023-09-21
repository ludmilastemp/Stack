#ifndef STL_error_
#define STL_error_

#include "STLstkconst.h"

void StackDump (const struct Stack* stk, const char* CALL_FILE, const size_t CALL_LINE);

int  StackErr  (struct Stack* stk, const char* CALL_FILE, const size_t CALL_LINE);

void StackPrintErr (const struct Stack* stk, const char* CALL_FILE, const size_t CALL_LINE);

#endif
