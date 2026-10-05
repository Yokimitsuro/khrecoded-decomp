#include "nitro/types.h"

typedef struct Hud {
    u8 pad_000[0x47c];
    s32 busy;
} Hud;

typedef struct HudHandle {
    u32 unk_00;
    Hud *hud;
} HudHandle;

extern HudHandle data_ov001_020a04c4;

extern BOOL func_ov001_020638ec(void);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);
extern BOOL IsFieldFlag8Set(void);
extern int func_ov001_02064784(void);
extern BOOL func_ov001_020645c8(u32 value);

BOOL CanOpenFieldMenu(void)
{
    BOOL result = TRUE;

    if (!func_ov001_020638ec()) {
        result = FALSE;
    }
    if (data_ov001_020a04c4.hud->busy != 0) {
        result = FALSE;
    }
    if (IsHudFlag7Set() || IsFieldFlag10Set() || IsFieldFlag8Set()) {
        result = FALSE;
    }
    if (!func_ov001_02064784() && func_ov001_020645c8(0x370b)) {
        result = FALSE;
    }
    return result;
}
