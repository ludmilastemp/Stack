#include "STL_stack_const.h"
#include "STL_stack_struct.h"

/// ��������� �����
struct Stack_int
{
#ifdef CANARY_PROTECTION
    CanaryType leftCanary;
#endif

#ifdef DEBUG
    size_t       CREATE_LINE;
    const char*  CREATE_FILE;
    const char*  CREATE_FUNC;
    const char*  CREATE_NAME;
#endif

    DataType* data;
    size_t size;
    size_t capacity;
    ErrorType err;

#ifdef HASH_PROTECTION
    long long hashStack;
    long long hashData;
#endif

#ifdef CANARY_PROTECTION
    CanaryType rightCanary;
#endif
};
