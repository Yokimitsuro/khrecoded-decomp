#include "nitro/types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 used;
} TextFrame;

extern void *func_ov039_020bc9b4(void);
extern BOOL InitTextLayerDefault(void *text, int layer, void *font, TextFrame *frame);
extern BOOL InitTextLayerAt(void *text, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern void FillBackgroundLayerRect(void *text, u16 *dst, u16 x, u16 y, u8 palette);
extern u16 *UpdateScreenWidgetLayer(int screen);
extern void SetScreenLayerDirty(int screen);

void OpenTextFrame(u32 position, u32 size, int layer, void *text, TextFrame *frame)
{
    u32 y;
    u32 x;
    u32 width;
    u32 height;
    int screen;
    u16 *screenBase;

    frame->x = x = (u16)position;
    frame->y = y = position >> 16;
    frame->width = width = (u16)size;
    frame->height = height = size >> 16;
    if (layer == 0) {
        InitTextLayerDefault(text, layer, func_ov039_020bc9b4(), frame);
    } else {
        if (layer < 4) {
            screen = layer + 8;
        } else {
            screen = layer + 0x14;
        }
        screenBase = UpdateScreenWidgetLayer(screen);
        InitTextLayerAt(text, layer, screenBase, func_ov039_020bc9b4(), frame);
        FillBackgroundLayerRect(text, screenBase, x, y, 0xf);
        SetScreenLayerDirty(screen);
    }
    frame->used += (u16)(width * height);
}
