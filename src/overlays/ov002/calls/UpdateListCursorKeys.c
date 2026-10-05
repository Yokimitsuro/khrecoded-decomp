#include "nitro/types.h"

extern u32 UpdateListCursor(void *input, void *list, u32 keys);

u32 UpdateListCursorKeys(u32 keys, void *list)
{
    return UpdateListCursor(NULL, list, keys);
}
