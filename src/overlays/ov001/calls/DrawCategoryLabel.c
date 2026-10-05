#include "nitro/types.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct MessageSet {
    void *file;
    u32 count;
    u8 *strings;
} MessageSet;

typedef struct TextCanvas {
    u8 pad_00[0x24];
    u8 *pixels;
} TextCanvas;

typedef struct TextLayer {
    u8 pad_00[0x20];
    TextCanvas *canvas;
    u8 pad_24[0x10];
} TextLayer;

typedef struct LabelWork {
    u8 pad_0000[0x3240];
    u8 upperTiles[0x3c0];
    u8 lowerTiles[0x240];
} LabelWork;

extern const TextFrame data_ov001_0209df3c;

extern u32 MakePrimaryVramKey_02073634(int index);
extern void LoadPackedFileView(MessageSet *messages, u32 key, int compressed);
extern int MapKindToCategory(int kind);
extern const u16 *func_ov027_020ba2c8(MessageSet *messages, int index);
extern void *GetSceneFont(void);
extern void InitTextLayerAt(TextLayer *layer, int bgLayer, void *charBase, void *font, TextFrame *frame);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void DrawTextAnchored(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void DestroyFndObjectList(TextLayer *layer);
extern void FreePointerIfSet(MessageSet *messages);

void DrawCategoryLabel(LabelWork *work, int kind)
{
    TextFrame frame = data_ov001_0209df3c;
    TextLayer layer;
    MessageSet messages;
    const u16 *text;
    u8 *pixels;

    LoadPackedFileView(&messages, MakePrimaryVramKey_02073634(0), 1);
    text = func_ov027_020ba2c8(&messages, MapKindToCategory(kind));
    InitTextLayerAt(&layer, 1, NULL, GetSceneFont(), &frame);
    pixels = layer.canvas->pixels;
    MIi_CpuCopyFast(work->upperTiles, pixels, 0x240);
    MIi_CpuCopyFast(work->lowerTiles, pixels + 0x240, 0x240);
    DrawTextAnchored(&layer, 0x25, 5, 0xf1, 0x411, text);
    DrawTextAnchored(&layer, 0x24, 4, 0xf2, 0x411, text);
    MIi_CpuCopyFast(pixels, work->upperTiles, 0x240);
    MIi_CpuCopyFast(pixels + 0x240, work->lowerTiles, 0x240);
    DestroyFndObjectList(&layer);
    FreePointerIfSet(&messages);
}
