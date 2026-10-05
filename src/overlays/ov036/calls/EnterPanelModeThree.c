#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_0000[6];
    u16 flags;
    s32 state;
    u8 pad_000c[0xe90 - 0xc];
    s32 primaryMode;
    u8 pad_0e94[0xea4 - 0xe94];
    s32 secondaryMode;
    u8 pad_0ea8[0x10e0 - 0xea8];
    s32 savedSlot;
    s32 timer;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;
extern u8 *data_ov001_020a0480;
extern int func_02029f5c(void);
extern int func_02029f6c(void);
extern void func_ov036_020ba840(char *name);
extern void ClearSessionPackedBit(int id);

void EnterPanelModeThree(char *name)
{
    PanelWork *work = data_ov036_020c3940.work;

    work->primaryMode = func_02029f5c();
    work->secondaryMode = func_02029f6c();
    if (work->secondaryMode != 0x10) {
        work->secondaryMode = -0x10;
    }
    func_ov036_020ba840(name);
    work->state = 3;
    work->flags |= 0x10;
    ClearSessionPackedBit(0x3309);
    ClearSessionPackedBit(0x3527);
    if (func_02029f5c() != 0) {
        work->savedSlot = data_ov001_020a0480[0x27f9];
    }
    data_ov036_020c3940.work->timer = 0x14;
}
