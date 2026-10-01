#include "libs/nitro/std/std_string_internal.h"

char *STD_ConcatenateString(char *destination, const char *source)
{
    int length = STD_GetStringLength(destination);
    (void)STD_CopyString(&destination[length], source);
    return destination;
}