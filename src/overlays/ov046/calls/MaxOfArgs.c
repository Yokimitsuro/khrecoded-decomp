#include "nitro/types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))
#define va_arg(ap, type) (*(type *)(((ap) += 4) - 4))
#define va_end(ap) ((void)0)

s32 MaxOfArgs(s32 count, ...)
{
    va_list args;
    s32 maxValue;
    u8 index;
    s32 value;

    va_start(args, count);
    maxValue = va_arg(args, s32);
    for (index = 1; index < count; index++) {
        value = va_arg(args, s32);
        if (maxValue < value) {
            maxValue = value;
        }
    }
    va_end(args);
    return maxValue;
}
