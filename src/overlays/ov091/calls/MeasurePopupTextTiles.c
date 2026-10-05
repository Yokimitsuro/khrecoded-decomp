#include "nitro/types.h"

typedef struct {
    int width;
    int height;
} TextSize;

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
    s32 stateTimer;
    s32 x;
    s32 y;
    s32 param;
    TextLayer textLayer;
} PopupWindow;

typedef struct {
    u8 pad_00[8];
    void *font;
} PopupManager;

extern PopupManager *data_ov091_020c375c;
extern BOOL InitTextLayerDefault(TextLayer *layer, int bg, void *font, void *frame);
extern TextSize NNSi_G2dFontGetTextRect(const void *font, int hSpace, int vSpace, const void *text);
extern BOOL DestroyFndObjectList(TextLayer *layer);

static inline TextSize MeasureLayerText(TextLayer *layer, const u16 *text)
{
    TextSize result = NNSi_G2dFontGetTextRect(layer->font, layer->hSpace, layer->vSpace, text);

    return result;
}

TextSize MeasurePopupTextTiles(PopupWindow *window, const u16 *text, void *frame, int padX, int padY)
{
    TextSize tiles;
    TextSize padded;
    TextSize size;

    InitTextLayerDefault(&window->textLayer, 6, data_ov091_020c375c->font, frame);
    size = MeasureLayerText(&window->textLayer, text);
    padded = size;
    padded.width += padX;
    padded.height += padY;
    tiles.width = padded.width / 8;
    if (padded.width % 8 > 0) {
        tiles.width++;
    }
    tiles.height = padded.height / 8;
    if (padded.height % 8 > 0) {
        tiles.height++;
    }
    if (tiles.width > 30) {
        tiles.width = 30;
    }
    if (tiles.height > 22) {
        tiles.height = 22;
    }
    DestroyFndObjectList(&window->textLayer);
    return tiles;
}
