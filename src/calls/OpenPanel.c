#include "nitro/types.h"

typedef struct PanelSlot {
    s32 timer;
    s32 mode;
} PanelSlot;

typedef struct PanelState {
    u64 openTick;
    u32 openFrame;
    u8 pages[0x68];
    PanelSlot slots[2];
    s32 blinkCounter;
    s32 blinkMode;
    u32 streamCursor;
    u8 pad_90[4];
    s32 selectedSlot;
    s32 field_98;
    u8 pad_9c[8];
    u32 visiblePlanes;
    u32 visibleWindows;
    u8 pad_ac[8];
    s32 field_b4;
    s32 active;
    s32 splitLayout;
    s32 state;
    s32 opened;
} PanelState;

extern PanelState *gPanelState;
extern u8 data_0205fdc4;
extern u8 sMain_PauseRefresh_02055f44[];
extern s32 func_ov001_02063a38(void);
extern u64 OS_GetTick(void);
extern u32 func_01ff80d4(void);
extern s32 func_020284fc(void);
extern BOOL IsSoundStreamActive(int handleIndex);
extern u32 GetNextStreamCursorOrInvalid(int handleIndex);
extern void StopSoundStreamAtIndex(int handleIndex, int fadeFrame);
extern void FadeBgmVolume(int a, int b);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void UpdatePanelScreenSetup(void);
extern void InvokeForChannelOrBoth(u32 arg0, void *arg1, void *arg2, int channel);

BOOL OpenPanel(void)
{
    PanelState *panel = gPanelState;

    if (func_ov001_02063a38() == 9) {
        return FALSE;
    }
    if (data_0205fdc4 == 0) {
        panel->active = 0;
        return FALSE;
    }
    panel->field_98 = 0;
    panel->openTick = OS_GetTick();
    panel->openFrame = func_01ff80d4();
    panel->field_b4 = 0;
    panel->splitLayout = func_020284fc();
    if (IsSoundStreamActive(0)) {
        panel->streamCursor = GetNextStreamCursorOrInvalid(0);
        StopSoundStreamAtIndex(0, 0);
    }
    FadeBgmVolume(0x40, 10);
    panel->selectedSlot = 0;
    MI_CpuFill8(&panel->blinkCounter, 0, 8);
    MI_CpuFill8(panel->slots, 0, 0x10);
    panel->slots[0].mode = 1;
    panel->opened = 1;
    panel->visiblePlanes = (*(vu32 *)0x04000000 & 0x1f00) >> 8;
    panel->visibleWindows = (*(vu32 *)0x04000000 & 0xe000) >> 13;
    InvokeForChannelOrBoth(1, sMain_PauseRefresh_02055f44, UpdatePanelScreenSetup, -1);
    return TRUE;
}
