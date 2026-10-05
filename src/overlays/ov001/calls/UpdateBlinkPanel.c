#include "nitro/types.h"

typedef struct BlinkFlags {
    s32 pendingA : 1;
    s32 pendingB : 1;
    s32 rest : 30;
} BlinkFlags;

typedef struct BlinkState {
    u8 pad_00[4];
    s32 active;
    s32 fading;
    u8 pad_0C[0x1a];
    u16 frame : 14;
    u16 mode : 2;
    BlinkFlags flags;
} BlinkState;

extern BlinkState *data_ov001_020a04f0;

extern int func_0202a7b8(void);
extern void TickBlinkTimer(BlinkState *blink);
extern void func_ov001_0207db78(BlinkState *blink);
extern void func_ov001_0207d870(BlinkState *blink);

BOOL UpdateBlinkPanel(void)
{
    BlinkState *blink = data_ov001_020a04f0;

    func_0202a7b8();
    if (blink->active != 0) {
        if (blink->flags.pendingB && blink->flags.pendingA) {
            blink->flags.pendingA = 0;
            blink->flags.pendingB = 0;
            blink->frame = 1;
        }
        TickBlinkTimer(blink);
        func_ov001_0207db78(blink);
        func_ov001_0207d870(blink);
    } else if (blink->fading != 0) {
        func_ov001_0207d870(blink);
    }
    return FALSE;
}
