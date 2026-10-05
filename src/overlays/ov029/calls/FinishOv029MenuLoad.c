#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} SceneState;

extern SceneState *data_ov029_020babc0;
extern BOOL UpdateMenuItemLoading(void);
extern BOOL AreAllListNodesReady(void);
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

int FinishOv029MenuLoad(void)
{
    int slotValue;
    u32 entryValue;

    if (!UpdateMenuItemLoading() || !AreAllListNodesReady()) {
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
    data_ov029_020babc0->flags |= 0x8000;
    return 4;
}
