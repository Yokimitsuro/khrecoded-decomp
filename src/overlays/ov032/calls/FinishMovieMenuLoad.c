#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} MovieState;

typedef struct {
    u8 pad_00[0x6f];
    u8 releasePxi;
} MovieConfig;

extern struct { MovieConfig *config; MovieState *state; } data_ov032_020c0080;
extern BOOL UpdateMenuItemLoading(void);
extern void func_ov001_020687b8(void);
extern void HighlightSelectedMenuPanels(void);
extern void InvokeSceneCallback(void);
extern int func_ov001_02067ed4(void);
extern int GetSlotEntryValue(int index);
extern int GetMenuItemValue(int index);
extern void SetCachedSoundParams(u32 param1, u32 param2, u16 param3);
extern void InvokeListNodeCallbacks(void);
extern void QueueAreaSoundArchives(void);
extern u32 func_ov001_020681d4(int index);
extern u32 func_ov001_020681c4(void);
extern void func_ov001_0207b0c0(u32 first, u32 second);
extern void func_ov001_02088270(int size);
extern void func_ov032_020ba624(void);

int FinishMovieMenuLoad(void)
{
    int slotValue;
    u32 entryValue;

    if (UpdateMenuItemLoading() == FALSE) {
        return -1;
    }
    func_ov001_020687b8();
    HighlightSelectedMenuPanels();
    InvokeSceneCallback();
    slotValue = GetSlotEntryValue(func_ov001_02067ed4());
    SetCachedSoundParams(slotValue, GetMenuItemValue(func_ov001_02067ed4()), 0x7f);
    InvokeListNodeCallbacks();
    QueueAreaSoundArchives();
    entryValue = func_ov001_020681d4(func_ov001_02067ed4());
    func_ov001_0207b0c0(func_ov001_020681c4(), entryValue);
    if (data_ov032_020c0080.config->releasePxi == 1) {
        func_ov001_02088270(0x96000);
    }
    func_ov032_020ba624();
    data_ov032_020c0080.state->flags |= 0x8000;
    return 5;
}
