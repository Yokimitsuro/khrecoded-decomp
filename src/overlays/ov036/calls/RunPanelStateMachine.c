#include "nitro/types.h"

typedef int (*PanelStateFn)(void);

typedef struct PanelWork {
    u8 pad_00[0x6];
    u16 flags;
    s32 state;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;
extern PanelStateFn gPanelScriptStateHandlers[];
extern void UpdatePendingSlotScene(void);
extern void func_ov036_020bb2a4(int arg);
extern void DrawPanelSceneFrame(void);

int RunPanelStateMachine(void)
{
    int next;

    do {
        data_ov036_020c3940.work->flags &= 0x7fff;
        next = gPanelScriptStateHandlers[data_ov036_020c3940.work->state]();
        if (next >= 0) {
            data_ov036_020c3940.work->state = next;
        }
    } while (data_ov036_020c3940.work->flags & 0x8000);
    UpdatePendingSlotScene();
    if (data_ov036_020c3940.work->flags & 8) {
        func_ov036_020bb2a4(0);
    }
    DrawPanelSceneFrame();
    return 0;
}
