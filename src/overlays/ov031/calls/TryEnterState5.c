#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void SetCachedSoundParams(u32 a, u32 b, u32 c);
extern u32 UpdateMenuItemLoading(void);
extern void InvokeSceneCallback(void);
extern void HighlightSelectedMenuPanels(void);
extern void QueueAreaSoundArchives(void);
extern u32 func_ov001_02067ed4(void);
extern u32 GetSlotEntryValue(void);
extern u32 GetMenuItemValue(void);
extern u32 func_ov001_020681c4(void);
extern u32 func_ov001_020681d4(void);
extern void func_ov001_020687b8(void);
extern void func_ov001_0207b0c0(u32 a, u32 b);
extern void InvokeListNodeCallbacks(void);
extern void func_ov001_020876f4(void);

u32 TryEnterState5(void)
{
    u32 result;
    u32 a;
    u32 b;

    result = UpdateMenuItemLoading();
    if (result == 0) {
        return 0xffffffff;
    }
    func_ov001_020876f4();
    func_ov001_020687b8();
    HighlightSelectedMenuPanels();
    InvokeSceneCallback();
    func_ov001_02067ed4();
    a = GetSlotEntryValue();
    func_ov001_02067ed4();
    b = GetMenuItemValue();
    SetCachedSoundParams(a, b, 0x7f);
    InvokeListNodeCallbacks();
    QueueAreaSoundArchives();
    func_ov001_02067ed4();
    a = func_ov001_020681d4();
    b = func_ov001_020681c4();
    func_ov001_0207b0c0(b, a);
    data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0x8000;
    return 5;
}
