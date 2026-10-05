#include "nitro/types.h"

typedef struct {
    int width;
    int height;
} TextRect;

typedef struct {
    u8 pad_00[0x14];
    void *font;
    int hSpace;
    int vSpace;
    u8 pad_20[0xe];
    u16 widthTiles;
    u16 heightTiles;
} TextLayer;

extern TextRect NNSi_G2dFontGetTextRect(const void *font, int hSpace, int vSpace, const void *text);
extern int MeasureTextWidth(void *font, const u16 *text, int maxLines);
extern void DrawTextColored(TextLayer *layer, int x, int y, int color, int altColor, const u16 *text);
extern void DrawTextAnchored(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void func_0200177c(TextLayer *layer, int x, int y, int color, int altColor, int shadowColor, const u16 *text, int unused);

static inline TextRect MeasureFontText(const void *font, int hSpace, int vSpace, const u16 *text)
{
    TextRect measured = NNSi_G2dFontGetTextRect(font, hSpace, vSpace, text);
    return measured;
}

static inline TextRect MeasureLayerText(TextLayer *layer, const u16 *text)
{
    return MeasureFontText(layer->font, layer->hSpace, layer->vSpace, text);
}

void DrawCenteredLayerText(TextLayer *layer, int x, int y, int color, int mode, const u16 *text)
{
    TextRect rect;

    if (x < 0 || y < 0) {
        rect = MeasureLayerText(layer, text);
        if (x < 0) {
            int lineWidth = MeasureTextWidth(layer, text, 0);
            x = (rect.width - lineWidth) / 2 + (layer->widthTiles * 8 - rect.width) / 2;
        }
        if (y < 0) {
            y = (layer->heightTiles * 8 - rect.height) / 2;
        }
    }
    if (mode == 0) {
        DrawTextColored(layer, x, y, color, 14, text);
    } else if (mode < 0) {
        func_0200177c(layer, x, y, color, 14, 13, text, 0);
    } else {
        DrawTextAnchored(layer, x, y, color, mode, text);
    }
}
