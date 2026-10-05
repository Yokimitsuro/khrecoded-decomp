#include "nitro/types.h"

typedef struct MapMenuState {
    u8 pad_00[0x2c];
    BOOL dirty;
} MapMenuState;

extern MapMenuState *data_ov023_020b6f84;

void MarkMapMenuDirty(void)
{
    data_ov023_020b6f84->dirty = TRUE;
}
