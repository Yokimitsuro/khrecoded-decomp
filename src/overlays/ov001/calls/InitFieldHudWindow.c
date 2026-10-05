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

typedef struct FieldGraphics {
    u8 pad_00[0x24];
    u8 *charData;
} FieldGraphics;

typedef struct FieldHud {
    u8 pad_00[0x34];
    u8 window[0x20];
    FieldGraphics *graphics;
    u8 pad_58[0x18];
    u8 *palettes;
} FieldHud;

typedef struct FieldScene {
    u8 pad_000[0x50c];
    MessageSet messages;
    u8 pad_518[0x38];
    FieldHud hud;
    u8 pad_5c4[0x4];
    BOOL bottomRowEnabled;
} FieldScene;

extern const TextFrame data_ov001_0209dc9c;
extern void *func_ov001_0207123c(void);
extern void *func_ov027_020b9e10(void *widgets, int layer);
extern void func_ov027_020b9e20(void *widgets, int layer);
extern void *GetFieldFont3(void);
extern void InitTextLayerAt(void *window, int bgLayer, void *charBase, void *font, TextFrame *frame);
extern void CallVirtualHandlerSlot1(void *window, int arg);
extern void FlushBufferAndRunCallback(void *window);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern u32 MakePrimaryVramKey_02073634(u32 messageId);
extern void LoadPackedFileView(MessageSet *messages, u32 fileId, int compressed);
extern void LoadFieldBottomRowTiles(FieldScene *scene);

void InitFieldHudWindow(FieldScene *scene, u8 *source)
{
    FieldHud *hud = &scene->hud;
    void *widgets = func_ov001_0207123c();
    TextFrame frame = data_ov001_0209dc9c;
    void *charBase = func_ov027_020b9e10(widgets, 9);
    u8 *charData;

    func_ov027_020b9e10(widgets, 0x19);
    InitTextLayerAt(hud->window, 1, charBase, GetFieldFont3(), &frame);
    CallVirtualHandlerSlot1(hud->window, 1);
    func_ov027_020b9e20(widgets, 9);
    hud->palettes = NNSi_FndAllocFromDefaultHeap(0x60);
    MIi_CpuCopyFast(source + 0x29c0, hud->palettes, 0x20);
    MIi_CpuCopyFast(source + 0x2a00, hud->palettes + 0x20, 0x20);
    MIi_CpuCopyFast(source + 0x2a80, hud->palettes + 0x40, 0x20);
    charData = hud->graphics->charData;
    MIi_CpuCopyFast(hud->palettes, charData, 0x20);
    MIi_CpuCopyFast(hud->palettes + 0x20, charData + 0x3a0, 0x20);
    MIi_CpuCopyFast(hud->palettes + 0x40, charData + 0x760, 0x20);
    FlushBufferAndRunCallback(hud->window);
    LoadPackedFileView(&scene->messages, MakePrimaryVramKey_02073634(2), 0);
    if (scene->bottomRowEnabled) {
        LoadFieldBottomRowTiles(scene);
    }
}
