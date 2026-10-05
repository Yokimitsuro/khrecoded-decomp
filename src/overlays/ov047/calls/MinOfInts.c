#include "nitro/types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))
#define va_arg(ap, type) (*(type *)(((ap) += 4) - 4))
#define va_end(ap) ((void)0)

int MinOfInts(int count, ...)
{
    va_list args;
    int result;
    u8 index;

    va_start(args, count);
    result = va_arg(args, int);
    for (index = 1; index < count; index++) {
        int value = va_arg(args, int);
        if (result > value) {
            result = value;
        }
    }
    va_end(args);
    return result;
}
