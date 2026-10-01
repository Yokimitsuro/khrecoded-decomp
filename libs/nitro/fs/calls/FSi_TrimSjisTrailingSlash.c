#include "libs/nitro/fs/fs_string_internal.h"

extern int STD_GetStringLength(const char *text);
extern int FSi_DecrementSjisPosition(const char *text, int position);

int FSi_TrimSjisTrailingSlash(char *text)
{
    int length = STD_GetStringLength(text);
    int lastPosition = FSi_DecrementSjisPosition(text, length);

    if (lastPosition >= 0 && FSi_IsSlash((u8)text[lastPosition])) {
        length = lastPosition;
        text[length] = '\0';
    }
    return length;
}
