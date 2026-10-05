#include "nitro/types.h"

#define ONE_SECOND_IN_TICKS 0x7fd88

typedef struct {
    u8 pad_000[0x1c];
    u8 recordPool[0x1fc - 0x1c];
    u8 captionWindow[0x2e4 - 0x1fc];
    u64 captionTick;
    u64 captionDuration;
    u8 pad_2f4[0x6ec - 0x2f4];
    s32 labelIds[4];
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;

extern void CallVirtualHandlerSlot1(void *window, int arg);
extern void DrawTextAnchored(void *window, u32 x, u32 y, u32 color, u32 flags, s32 labelId);
extern void Text_UploadTileBuffer(void *window);
extern u16 *func_ov027_020b9e10(HudContext *context, int layer);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void FillBackgroundLayerRect(void *window, u16 *dst, int x, int y, u8 palette);

void ShowHudCaption(int labelIndex) {
    HudContext *context = data_ov001_020a04c4.context;
    if (labelIndex != -1) {
        s32 labelId = context->labelIds[labelIndex];
        u16 *layer;
        CallVirtualHandlerSlot1(context->captionWindow, 1);
        DrawTextAnchored(context->captionWindow, 0x70, 3, 2, 0x11, labelId);
        Text_UploadTileBuffer(context->captionWindow);
        layer = func_ov027_020b9e10(context, 0xb);
        func_ov027_020b8230(context->recordPool, FindActiveRecordById(context->recordPool, 6));
        FillBackgroundLayerRect(context->captionWindow, layer, 2, 1, 0xf);
        context->captionTick = 0;
        context->captionDuration = ONE_SECOND_IN_TICKS;
    }
}
