#include "libs/nitro/std/std_string_internal.h"

char *STD_CopyString(char *destination, const char *source)
{
    char *result = destination;

    while (*source) {
        *destination++ = *source++;
    }
    *destination = 0;
    return result;
}