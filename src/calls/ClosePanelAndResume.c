#include "nitro/types.h"
#include "nitro/hw.h"

typedef struct PanelState {
    u64 savedTick;
    u32 savedValue;
    u8 pad_0C[0x80];
    s32 streamOffset;
    u8 pad_90[0x24];
    s32 confirmed;
    u8 pad_B8[0x8];
    s32 fadeEngine;
    s32 fadePending;
} PanelState;

extern PanelState *data_0205fe24;
extern u8 sMain_PoffRefresh_02055f54[];

extern s32 func_ov001_02063a38(void);
extern void OS_SetTick(u64 count);
extern u32 func_020011a8(u32 value);
extern void SNDi_BroadcastChannelOp(int arg0);
extern void StartSoundStreamAtOffset(int handleIndex, u32 offset);
extern void FadeBgmVolume(int targetVolume, int frames);
extern void InvokeForChannelOrBoth(u32 arg0, u32 arg1, int arg2, int channel);
extern BOOL IsSoundStreamActive(int handleIndex);
extern void StopSoundStreamAtIndex(int handleIndex, int fadeFrame);
extern void func_020281e0(void);

static inline void SetVisiblePlane(int plane)
{
    *(vu32 *)REG_DISPCNT_ADDR = (*(vu32 *)REG_DISPCNT_ADDR & ~0x1f00) | (plane << 8);
}

BOOL ClosePanelAndResume(void)
{
    PanelState *panel = data_0205fe24;

    if (func_ov001_02063a38() != 8) {
        SetVisiblePlane(1);
    } else {
        SetVisiblePlane(3);
    }
    OS_SetTick(panel->savedTick);
    func_020011a8(panel->savedValue);
    SNDi_BroadcastChannelOp(0);
    if (panel->confirmed == 0 && panel->streamOffset != -1) {
        StartSoundStreamAtOffset(0, panel->streamOffset);
    }
    FadeBgmVolume(0x7f, 10);
    panel->streamOffset = -1;
    if (panel->confirmed == 0) {
        panel->fadePending = 1;
        InvokeForChannelOrBoth(1, (u32)sMain_PoffRefresh_02055f54, (int)func_020281e0, -1);
    } else {
        panel->fadeEngine = 3;
        if (IsSoundStreamActive(0)) {
            StopSoundStreamAtIndex(0, 0);
        }
    }
    panel->confirmed = 0;
    return TRUE;
}
