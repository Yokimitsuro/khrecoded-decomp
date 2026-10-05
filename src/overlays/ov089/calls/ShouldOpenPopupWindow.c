#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x744];
    s32 entryCount;
} Ov089Menu;

extern BOOL func_ov001_020645c8(u32 flagId);

BOOL ShouldOpenPopupWindow(Ov089Menu *menu)
{
    if (func_ov001_020645c8(0xff4) == FALSE && menu->entryCount > 1) {
        return TRUE;
    }
    return FALSE;
}
