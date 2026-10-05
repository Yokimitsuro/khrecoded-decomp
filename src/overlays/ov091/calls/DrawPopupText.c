#include "nitro/types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 pad_08;
    u16 palette;
} TextFrame;

typedef struct {
    u8 pad_00[0x14];
    void *font;
    int hSpace;
    int vSpace;
    u8 pad_20[0x14];
} TextLayer;

typedef struct {
    s32 state;
    u32 flags;
    u8 pad_08[0x10];
    TextLayer textLayer;
    u16 *text;
    TextFrame frame;
} PopupWindow;

typedef struct {
    u8 pad_00[8];
    void *font;
} PopupManager;

extern PopupManager *data_ov091_020c375c;
extern u32 func_ov091_020c2798(PopupWindow *window, u32 mask);
extern void func_ov091_020c2774(PopupWindow *window, u32 mask);
extern BOOL InitTextLayerAt(TextLayer *layer, int bg, u16 *screenBase, void *font, TextFrame *frame);
extern int NNSi_G2dFontGetTextWidth(const void *font, int hSpace, const void *text);
extern int NNSi_G2dFontGetTextHeight(const void *font, int vSpace, const void *text);
extern void CallVirtualHandlerSlot1(TextLayer *layer, int color);
extern void DrawTextPackedColor(void *context, int x, int y, int color, int flags, int highColor, const u16 *text);
extern void FlushBufferAndRunCallback(TextLayer *layer);
extern void *G2S_GetBG2ScrPtr(void);
extern void FillBackgroundLayerRect(TextLayer *layer, u16 *dst, int x, int y, u8 palette);

void DrawPopupText(PopupWindow *window)
{
    TextFrame *frame;
    int textWidth;
    int textHeight;
    int x;
    int y;

    if (func_ov091_020c2798(window, 1)) {
        return;
    }
    frame = &window->frame;
    InitTextLayerAt(&window->textLayer, 6, NULL, data_ov091_020c375c->font, frame);
    textWidth = NNSi_G2dFontGetTextWidth(window->textLayer.font, window->textLayer.hSpace, window->text);
    textHeight = NNSi_G2dFontGetTextHeight(window->textLayer.font, window->textLayer.vSpace, window->text);
    x = (frame->width * 8) / 2 - textWidth / 2;
    y = (frame->height * 8) / 2 - textHeight / 2 - 1;
    CallVirtualHandlerSlot1(&window->textLayer, 5);
    DrawTextPackedColor(&window->textLayer, x, y, 2, 2, 7, window->text);
    FlushBufferAndRunCallback(&window->textLayer);
    FillBackgroundLayerRect(&window->textLayer, G2S_GetBG2ScrPtr(), window->frame.x, frame->y, frame->palette);
    func_ov091_020c2774(window, 1);
}
