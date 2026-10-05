#include "nitro/types.h"

typedef struct TextFrame {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 palette;
    s16 pad_0a[3];
} TextFrame;

typedef struct TitleIdTable {
    s32 ids[8];
} TitleIdTable;

typedef struct FontResource {
    u32 words[3];
} FontResource;

typedef struct TextLayer {
    u8 data[0x34];
} TextLayer;

typedef struct PackedFileView {
    u32 words[3];
} PackedFileView;

typedef struct MenuEntry {
    s32 id;
    s32 textId;
} MenuEntry;

typedef struct Ov037Context {
    u16 selected;
    u16 entryCount;
    s32 rowOffset;
    u8 list[0x4c];
    u8 tileTable[0x1c];
    u8 model[0x128];
    u8 camera[0x38];
    s32 enabled;
    MenuEntry entries[4];
    TextLayer text;
} Ov037Context;

extern Ov037Context *gContinueScreenContext;
extern const TextFrame data_ov037_020bb66c;
extern const TitleIdTable data_ov037_020bb690;
extern char sOv037_TextFontEu10Nftr_020bb758[];
extern char sOv037_CntConLanguageSZ_020bb770[];
extern u16 *func_ov027_020b9e10(void *tileTable, int row);
extern int func_0200146c(FontResource *font, char *path);
extern BOOL InitTextLayerAt(TextLayer *layer, int plane, u16 *screen, FontResource *font, TextFrame *frame);
extern void LoadPackedFileView(PackedFileView *view, char *path, BOOL fromTail);
extern void *func_ov027_020ba2c8(PackedFileView *view, int index);
extern void DrawTextAnchored(TextLayer *layer, int x, int y, int color, u32 flags, const void *text);
extern void FlushBufferAndRunCallback(TextLayer *layer);
extern void DestroyFndObjectList(TextLayer *layer);
extern s8 func_ov001_02068084(void);
extern s32 func_ov037_020bad2c(void);
extern BOOL FreeResourceBufferAndProbeHeap(FontResource *font);
extern void FreePointerIfSet(PackedFileView *view);
extern void func_ov027_020b9e20(void *tileTable, int row);

void DrawMenuTexts(void)
{
    TextFrame frame = data_ov037_020bb66c;
    FontResource font;
    TextLayer layer;
    PackedFileView view;
    TitleIdTable titleIds;
    u16 *screen;
    int index;
    int mode;
    s32 titleIndex;

    titleIds = data_ov037_020bb690;
    frame.y = gContinueScreenContext->rowOffset;
    frame.height = 0x18 - gContinueScreenContext->rowOffset;
    screen = func_ov027_020b9e10(gContinueScreenContext->tileTable, 10);
    func_0200146c(&font, sOv037_TextFontEu10Nftr_020bb758);
    InitTextLayerAt(&layer, 2, screen, &font, &frame);
    LoadPackedFileView(&view, sOv037_CntConLanguageSZ_020bb770, TRUE);
    for (index = 0; index < gContinueScreenContext->entryCount; index++) {
        DrawTextAnchored(&layer, 0x38, index * 16 + 3, 2, 0x411,
                                  func_ov027_020ba2c8(&view, gContinueScreenContext->entries[index].textId));
    }
    FlushBufferAndRunCallback(&layer);
    DestroyFndObjectList(&layer);
    frame.x = 0;
    frame.y = 2;
    frame.width = 0x20;
    frame.height = 4;
    frame.palette = 0x8d;
    mode = func_ov001_02068084();
    titleIndex = func_ov037_020bad2c();
    InitTextLayerAt(&gContinueScreenContext->text, 2, screen, &font, &frame);
    FlushBufferAndRunCallback(&gContinueScreenContext->text);
    if (titleIndex >= 0) {
        DrawTextAnchored(&gContinueScreenContext->text, 0x80, 0x10, 2, 0x212,
                                  func_ov027_020ba2c8(&view, titleIndex + titleIds.ids[mode]));
    }
    FreeResourceBufferAndProbeHeap(&font);
    FreePointerIfSet(&view);
    func_ov027_020b9e20(gContinueScreenContext->tileTable, 10);
}
