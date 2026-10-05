#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x2c67];
    u8 unlockCount;
} SaveBlock;

extern SaveBlock *data_0205fe0c;
extern s32 func_ov075_020c49a8(void);

BOOL HasPendingUnlocks(void)
{
    s32 flaggedCount = func_ov075_020c49a8();

    if (data_0205fe0c->unlockCount < flaggedCount) {
        return TRUE;
    }
    return FALSE;
}
