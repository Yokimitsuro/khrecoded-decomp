#include "nitro/types.h"

typedef struct MapMenuState {
    u8 pad_00[0x8];
    void *mapImage;
    void *markerImage;
    u8 pad_10[0x10];
    int mode;
    u8 pad_24[0x18];
    BOOL routeOpen;
    u8 pad_40[0x4];
    void *listener;
} MapMenuState;

extern MapMenuState *data_ov023_020b6f84;
extern char sOv023_UiBtlMapLanguageP2_020b6f40[];
extern char sOv023_UiBtlMapchrP2_020b6f50[];

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, u32 val, u32 size);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern BOOL IsFieldFlag8Set(void);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern int func_ov001_02064784(void);
extern void *Msg_OpenContainerAndReadHeader(const char *path, int arg1, int arg2);
extern void InitMapScreen(MapMenuState *state);
extern void *AddFieldListener(int value);
extern u8 func_ov001_0207b484(void);
extern void ApplyFormationSlots(int formationType);
extern void RefreshScaledMenuScreen(void);
extern void *UpdateMapMenuState(void);

void *InitMapMenuState(void)
{
    MapMenuState *state = NNSi_FndGetCurrentRootHeap();
    data_ov023_020b6f84 = state;
    MI_CpuFill8(state, 0, 0x7fc4);
    if (func_ov001_020645c8(0x3520) || IsFieldFlag13OrSessionFlagSet() || IsFieldFlag8Set()) {
        if (func_ov001_020645c8(0x3520) && ReadSessionPackedBits(0x1a00, 2) == 1 && !func_ov001_02064784()) {
            state->routeOpen = TRUE;
        } else {
            state->routeOpen = FALSE;
        }
    } else {
        state->routeOpen = TRUE;
    }
    state->mode = 1;
    state->mapImage = Msg_OpenContainerAndReadHeader(sOv023_UiBtlMapLanguageP2_020b6f40, 0xe, 0);
    state->markerImage = Msg_OpenContainerAndReadHeader(sOv023_UiBtlMapchrP2_020b6f50, 0xe, 0);
    InitMapScreen(state);
    state->listener = AddFieldListener((int)RefreshScaledMenuScreen);
    ApplyFormationSlots(func_ov001_0207b484());
    return UpdateMapMenuState;
}
