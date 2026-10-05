#include "nitro/types.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 tileOffset;
    u16 unk_a;
    u16 unk_c;
    u16 unk_e;
} TextFrame;

typedef struct WidgetSetup {
    u32 values[5];
} WidgetSetup;

extern u32 data_ov025_020b7780;
extern WidgetSetup data_ov025_020b76e0;
extern TextFrame data_ov025_020b76d0;

extern void func_ov027_020b7d78(u32 container, WidgetSetup *setup);
extern void *func_ov001_0207123c(void);
extern void func_ov027_020b9d38(void *table, int id);
extern u16 *func_ov027_020b9e10(void *owner, int layerId);
extern void *GetFieldFont3(void);
extern void *GetFieldFont2(void);
extern BOOL InitTextLayerAtFromEnd(void *obj, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern int CountActiveSlots(u32 entity);
extern void DrawRemainingCountText(u32 screen, int count);
extern u32 func_ov001_02073684(void);
extern void func_02001620(void *context, u32 x, u32 y, u32 color, u32 flags, u32 text, void *font, int maxWidth);
extern void Text_UploadTileBuffer(void *context);
extern void FlushBufferAndRunCallback(void *context);
extern void func_ov027_020b9e20(void *table, int id);
extern void GXS_LoadBG0Scr(const void *src, u32 offset, u32 size);
extern void func_ov027_020b90a8(u32 container, int id, void *handler);
extern void HandleDefaultMenuAction(void);
extern u32 func_ov025_020b5e44(void);

void *SetupMenuTextLayers(void)
{
    u32 menu = data_ov025_020b7780;
    WidgetSetup setup = data_ov025_020b76e0;
    TextFrame frame;
    void *tileTable;
    u16 *screenBase;

    func_ov027_020b7d78(menu, &setup);
    frame = data_ov025_020b76d0;
    tileTable = func_ov001_0207123c();
    func_ov027_020b9d38(tileTable, 0x18);
    screenBase = func_ov027_020b9e10(tileTable, 0x18);
    InitTextLayerAtFromEnd((void *)(menu + 0x6634), 4, screenBase, GetFieldFont3(), &frame);
    DrawRemainingCountText(menu, CountActiveSlots(menu + 0x64f4));

    frame.x = 2;
    frame.y = 0;
    frame.width = 0xb;
    frame.height = 2;
    frame.tileOffset = 0x1a0;
    InitTextLayerAtFromEnd((void *)(menu + 0x6668), 4, screenBase, GetFieldFont3(), &frame);
    func_02001620((void *)(menu + 0x6668), 1, 3, 2, 0x209, func_ov001_02073684(), GetFieldFont2(), 0x50);
    if (*(u8 *)(menu + 0x64e9) != 0) {
        FlushBufferAndRunCallback((void *)(menu + 0x6668));
    } else {
        Text_UploadTileBuffer((void *)(menu + 0x6668));
    }

    frame.x = 0;
    frame.y = 0x15;
    frame.width = 0x1d;
    frame.height = 3;
    frame.tileOffset += 0x16;
    InitTextLayerAtFromEnd((void *)(menu + 0x669c), 4, screenBase, GetFieldFont3(), &frame);
    func_02001620((void *)(menu + 0x669c), 4, 0, 2, 0x209, func_ov001_02073684(), GetFieldFont2(), 0xe4);
    if (*(u8 *)(menu + 0x64e9) != 0) {
        FlushBufferAndRunCallback((void *)(menu + 0x669c));
    } else {
        Text_UploadTileBuffer((void *)(menu + 0x669c));
    }

    func_ov027_020b9e20(tileTable, 0x18);
    if (*(u8 *)(menu + 0x64e9) != 0) {
        GXS_LoadBG0Scr(screenBase, 0, 0x800);
    }
    *(int *)(menu + 0x66d8) = 1;
    func_ov027_020b90a8(menu + 0x4c, 3, HandleDefaultMenuAction);
    return func_ov025_020b5e44;
}
