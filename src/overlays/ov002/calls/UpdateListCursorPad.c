#include "nitro/types.h"

extern u16 data_02060500;
extern u32 func_ov002_02062fb4(void *input, void *list, u32 keys);

u32 UpdateListCursorPad(void *input, void *list)
{
    return func_ov002_02062fb4(input, list, data_02060500);
}
