#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    void *font;
    int hSpace;
    int vSpace;
    u8 pad_20[0x14];
} TextLayer;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 unk_08;
    u16 palette;
} TextFrame;

typedef struct {
    int state;
    u32 flags;
    int frameCount;
    u8 pad_0c[0xc];
    TextLayer textLayer;
    const u16 *text;
    TextFrame frame;
} PopupState;

typedef struct {
    u8 pad_00[8];
    void *font;
} PopupManager;

extern PopupManager *data_ov093_020c5104;
extern u32 func_ov093_020c3bd8(PopupState *popup, u32 mask);
extern void func_ov093_020c3bb4(PopupState *popup, u32 mask);
extern BOOL InitTextLayerAt(TextLayer *layer, int layerIndex, u16 *screenBase, void *font, TextFrame *frame);
extern int NNSi_G2dFontGetTextWidth(void *font, int hSpace, const void *text);
extern int NNSi_G2dFontGetTextHeight(void *font, int vSpace, const void *text);
extern void CallVirtualHandlerSlot1(TextLayer *layer, int arg);
extern void DrawTextColored(TextLayer *layer, int x, int y, int color, int altColor, const u16 *text);
extern void FlushBufferAndRunCallback(TextLayer *layer);
extern void *G2S_GetBG2ScrPtr(void);
extern void FillBackgroundLayerRect(TextLayer *layer, void *dst, int x, int y, u8 palette);

void DrawPopupText_020c2e24(PopupState *popup)
{
    TextFrame *frame;
    int width;
    int height;
    int x;
    int y;

    if (func_ov093_020c3bd8(popup, 1) != 0) {
        return;
    }
    frame = &popup->frame;
    InitTextLayerAt(&popup->textLayer, 6, NULL, data_ov093_020c5104->font, frame);
    width = NNSi_G2dFontGetTextWidth(popup->textLayer.font, popup->textLayer.hSpace, popup->text);
    height = NNSi_G2dFontGetTextHeight(popup->textLayer.font, popup->textLayer.vSpace, popup->text);
    x = frame->width * 8 / 2 - width / 2;
    y = frame->height * 8 / 2 - height / 2 - 1;
    CallVirtualHandlerSlot1(&popup->textLayer, 6);
    DrawTextColored(&popup->textLayer, x, y, 2, 7, popup->text);
    FlushBufferAndRunCallback(&popup->textLayer);
    FillBackgroundLayerRect(&popup->textLayer, G2S_GetBG2ScrPtr(), popup->frame.x, frame->y, frame->palette);
    func_ov093_020c3bb4(popup, 1);
}
