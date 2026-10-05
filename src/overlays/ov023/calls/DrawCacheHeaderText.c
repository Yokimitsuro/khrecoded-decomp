#include "nitro/types.h"

typedef struct {
    u32 handle;
    u8 pad_04[4];
    u32 entryCount;
    u8 textWidget[0x34];
} ResourceCacheState;

extern ResourceCacheState *data_ov023_020b6f80;
extern void CallVirtualHandlerSlot1(void *widget, int mode);
extern int GetFieldFont2(void);
extern void func_02001620(void *widget, u32 x, u32 y, u32 color, u32 flags, int text,
                          u32 overrideValue, int maxWidth);
extern void Text_UploadTileBuffer(void *widget);

void DrawCacheHeaderText(int text)
{
    ResourceCacheState *state = data_ov023_020b6f80;
    void *widget;
    u32 overrideValue;

    if (state != NULL && text != 0 && state->entryCount != 0) {
        widget = state->textWidget;
        CallVirtualHandlerSlot1(widget, 1);
        overrideValue = GetFieldFont2();
        func_02001620(widget, 0xab, 3, 2, 0x821, text, overrideValue, 0xa8);
        Text_UploadTileBuffer(widget);
    }
}
