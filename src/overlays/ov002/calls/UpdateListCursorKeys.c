#include "nitro/types.h"

extern u32 func_ov002_02062fb4(void *input, void *list, u32 keys);

u32 UpdateListCursorKeys(u32 keys, void *list)
{
    return func_ov002_02062fb4(NULL, list, keys);
}
