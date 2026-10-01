#include "libs/nitro/fs/fs_string_internal.h"

int FSi_DecrementSjisPosition(const char *text, int position)
{
    int previous = --position;

    for (; previous > 0 && STD_IsSjisLeadByte(text[previous - 1]); --previous) {
    }
    return position - ((position - previous) & 1);
}
