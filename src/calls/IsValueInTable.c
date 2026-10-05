#include "nitro/types.h"

extern s32 data_020534e4[];

BOOL IsValueInTable(s32 value)
{
    s32 index = 0;

    do {
        if (value == data_020534e4[index]) {
            return FALSE;
        }
        index = index + 1;
    } while (index < 0x13);

    return TRUE;
}
