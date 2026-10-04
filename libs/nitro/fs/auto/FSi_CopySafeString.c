#include "libs/nitro/fs/fs_internal.h"

int FSi_CopySafeString(char *destination, int destinationLength,
                       const char *source, int sourceLength,
                       BOOL *stickyFailure)
{
    int position;
    int length = destinationLength - 1 < sourceLength
                     ? destinationLength - 1
                     : sourceLength;

    for (position = 0;
         position < length && source[position] != '\0';
         ++position) {
        destination[position] = source[position];
    }
    if (position < sourceLength && source[position] != '\0') {
        *stickyFailure = 1;
    }
    destination[position] = '\0';
    return position;
}