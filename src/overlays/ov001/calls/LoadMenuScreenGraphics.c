#include "nitro/types.h"

typedef struct CharData {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharData;

typedef struct ScreenData {
    u8 pad_00[8];
    u32 size;
    void *data;
} ScreenData;

typedef struct BgGraphicsData {
    u32 unk0;
    CharData *character;
    ScreenData *screen;
} BgGraphicsData;

typedef struct PaletteData {
    u8 pad_00[0xc];
    void *raw;
} PaletteData;

typedef struct LayerConfig {
    u32 words[5];
} LayerConfig;

typedef struct CellConfig {
    u32 words[7];
} CellConfig;

typedef struct CellDesc {
    CellConfig *cells;
    int count;
    u16 width;
    u16 height;
    int flags;
} CellDesc;

typedef struct MenuScreen {
    u8 pad_000[0x1c];
    u8 layer[0x4c];
    int archiveBase;
    u8 pad_06c[0x404];
    void *palette;
    u8 pad_474[0x1a0];
    void *screenArchive;
    BgGraphicsData screenBg;
} MenuScreen;

extern const LayerConfig data_ov001_0209dcbc;
extern const CellConfig data_ov001_0209dd0c;
extern void InitTileTableFrom(MenuScreen *screen, CellDesc *desc);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void GX_LoadBGPltt(void *dest, u32 srcOffset, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void func_ov027_020b7d78(void *container, LayerConfig *configuration);
extern void func_ov027_020b7e44(void *ctx, u32 fileId);
extern void *Archive_LoadFile(u32 fileId, u32 mode);
extern void *func_0202c4a0(u32 fileId, u32 mode);
extern BOOL NNS_G2dGetUnpackedPaletteData(void *pNclrFile, PaletteData **ppPltData);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

void LoadMenuScreenGraphics(MenuScreen *screen, BgGraphicsData *bg, void *archive) {
    LayerConfig layer = data_ov001_0209dcbc;
    CellConfig cells = data_ov001_0209dd0c;
    CellDesc desc;
    PaletteData *palette;
    void *nclr;

    desc.cells = &cells;
    desc.count = 7;
    desc.width = 0x20;
    desc.height = 0x20;
    desc.flags = 0;
    InitTileTableFrom(screen, &desc);
    GetBgDataFromArchive(bg, archive, -1, 0, 0);
    GX_LoadBGPltt(bg->screen->data, 0, bg->screen->size);
    GX_LoadBG3Char(bg->character->data, 0, bg->character->size);
    func_ov027_020b7d78(screen->layer, &layer);
    func_ov027_020b7e44(screen->layer, ((screen->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000000);
    screen->screenArchive = Archive_LoadFile(((screen->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000003, 0xe);
    GetBgDataFromArchive(&screen->screenBg, screen->screenArchive, -1, 0, 0);
    nclr = func_0202c4a0(((screen->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000068, 0xe);
    NNS_G2dGetUnpackedPaletteData(nclr, &palette);
    screen->palette = NNSi_FndAllocFromDefaultHeap(0x80);
    MIi_CpuCopyFast(palette->raw, screen->palette, 0x80);
    NNSi_FndFreeFromDefaultHeap(nclr);
}
