#include "libs/nitro/fs/fs_string_internal.h"

int FSi_IncrementSjisPositionToSlash(const char *text, int position)
{
    while (text[position] && !FSi_IsSlash((u8)text[position])) {
        position = FSi_IncrementSjisPosition(text, position);
    }
    return position;
}
