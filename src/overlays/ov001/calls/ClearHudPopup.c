#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c];
    u8 recordPool[0x18c - 0x1c];
    u8 popupWindow[0x40c - 0x18c];
    u64 popupTick;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;

extern void CallVirtualHandlerSlot1(void *window, int arg);
extern void Text_UploadTileBuffer(void *window);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8288(void *pool, void *record);

void ClearHudPopup(void) {
    HudContext *context = data_ov001_020a04c4.context;
    if (context->popupTick != 0) {
        CallVirtualHandlerSlot1(context->popupWindow, 1);
        Text_UploadTileBuffer(context->popupWindow);
        func_ov027_020b8288(context->recordPool, FindActiveRecordById(context->recordPool, 0x34));
        context->popupTick = 0;
    }
}
