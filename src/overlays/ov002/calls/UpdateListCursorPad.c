#include "nitro/types.h"

extern u16 data_02060500;
extern u32 UpdateListCursor(void *input, void *list, u32 keys);

u32 UpdateListCursorPad(void *input, void *list)
{
    return UpdateListCursor(input, list, data_02060500);
}
