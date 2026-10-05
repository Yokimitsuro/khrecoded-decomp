#include "nitro/types.h"

extern u32 data_ov025_020b7780;

extern void CallVirtualHandlerSlot1(void *entry, int mode);
extern int func_ov001_02073684(void);
extern int GetFieldFont2(void);
extern void func_02001620(int *context, u32 x, u32 y, u32 color, u32 flags, int value,
                           u32 overrideValue, int maxWidth);
extern void Text_UploadTileBuffer(void *entry);

void DrawNumberInPanelSlot(void) {
    u32 ctx = data_ov025_020b7780;
    u32 slot = ctx + 0x6668;
    int value;
    int overrideValue;

    CallVirtualHandlerSlot1((void *)slot, 0);
    value = func_ov001_02073684();
    overrideValue = GetFieldFont2();
    func_02001620((int *)slot, 4, 0, 2, 0x209, value, overrideValue, 0x70);
    Text_UploadTileBuffer((void *)slot);
}
