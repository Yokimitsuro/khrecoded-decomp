#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct GraphicsView {
    NNSG2dScreenData *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} GraphicsView;

typedef struct HudContext {
    u8 pad_000[0x1c];
    u8 recordPool[0x624 - 0x1c];
    u16 iconPalettes[1][0x30];
} HudContext;

typedef struct HudGlobals {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern u32 MakePrimaryVramKey(u32 index);
extern void *func_0202c4a0(u32 fileId, u32 heapId);
extern void GetBgDataFromArchive(GraphicsView *view, void *file, int screenIndex, int characterIndex, int paletteIndex);
extern void DC_FlushRange(void *buffer, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void LoadSlotIconGraphics(int slot, int iconId)
{
    HudContext *context = data_ov001_020a04c4.context;
    void *file;
    GraphicsView view;

    func_ov027_020b8230(context->recordPool, FindActiveRecordById(context->recordPool, slot + 8));
    func_ov027_020b8230(context->recordPool, FindActiveRecordById(context->recordPool, slot + 2));
    file = func_0202c4a0(MakePrimaryVramKey(iconId + 8), 0xe);
    GetBgDataFromArchive(&view, file, -1, 0, 0);
    DC_FlushRange(view.character->pRawData, view.character->szByte);
    DC_FlushRange(view.palette->pRawData, view.palette->szByte);
    GX_LoadBG3Char(view.character->pRawData, (slot * 9 + 0x2c) * 0x20, view.character->szByte);
    GX_LoadBGPltt(view.palette->pRawData, (slot + 3) * 0x20, 0x20);
    MIi_CpuCopy16(view.palette->pRawData, context->iconPalettes[slot], 0x60);
    NNSi_FndFreeFromDefaultHeap(file);
}
