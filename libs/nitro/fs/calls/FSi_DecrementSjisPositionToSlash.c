#include "libs/nitro/fs/fs_string_internal.h"

extern int FSi_DecrementSjisPosition(const char *text, int position);

int FSi_DecrementSjisPositionToSlash(const char *text, int position)
{
    for (;;) {
        position = FSi_DecrementSjisPosition(text, position);
        if (position < 0 || FSi_IsSlash((u8)text[position])) {
            break;
        }
    }
    return position;
}
