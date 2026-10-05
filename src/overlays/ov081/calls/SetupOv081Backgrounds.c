#include "nitro/types.h"

typedef struct ScreenData {
    u8 pad_00[0x8];
    u32 size;
    u8 rawData[1];
} ScreenData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *rawData;
} CharacterData;

typedef struct PaletteData {
    u8 pad_00[0x8];
    u32 size;
    void *rawData;
} PaletteData;

typedef struct BgGraphicsData {
    ScreenData *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct Ov081State {
    u32 archive;
    u8 pad_04[0x61c];
    u8 titleTiles[1];
} Ov081State;

extern void G2x_SetBlendAlpha_(vu32 *reg, int plane1, int plane2, int ev1, int ev2);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void *func_0202c4a0(u32 fileId, int heapId);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Scr(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern const void *func_ov081_020c5c04(int id);
extern void func_ov081_020c5550(void *charBase, int bg, const void *text, int x, int y, int areaWidth,
                                     int areaHeight, int tile);

static inline void SetWindowOutsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x0400004a & ~0x3f) | planeMask;
    if (effect) {
        value |= 0x20;
    }
    *(vu16 *)0x0400004a = (u16)value;
}

static inline void SetWindow0InsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x04000048 & ~0x3f) | planeMask;
    if (effect) {
        value |= 0x20;
    }
    *(vu16 *)0x04000048 = (u16)value;
}

static inline void SetWindow1InsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x04000048 & ~0x3f00) | (planeMask << 8);
    if (effect) {
        value |= 0x2000;
    }
    *(vu16 *)0x04000048 = (u16)value;
}

void SetupOv081Backgrounds(Ov081State *state)
{
    void *archive;
    BgGraphicsData bg;

    G2x_SetBlendAlpha_((vu32 *)0x04000050, 1, 0x1e, 16, 16);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;
    *(vu16 *)0x04000008 = (u16)((*(vu16 *)0x04000008 & ~3) | 0);
    *(vu16 *)0x0400000a = (u16)((*(vu16 *)0x0400000a & ~3) | 1);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & ~3) | 2);
    *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & ~3) | 3);
    *(vu32 *)0x04000014 = 0x30000;
    *(vu32 *)0x04000018 = 0x1fc0000;
    *(vu32 *)0x0400001c = 0;
    SetWindowOutsidePlane(0x1f, TRUE);
    SetWindow0InsidePlane(0x1f, TRUE);
    SetWindow1InsidePlane(0x1f, TRUE);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0xe000) | 0x6000;
    *(vu16 *)0x0400000a = (u16)((*(vu16 *)0x0400000a & 0x43) | 0xa0);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & 0x43) | 0x1a0);
    *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & 0x43) | 0x230);

    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x600);
    MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x600);
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x600);

    archive = func_0202c4a0((((state->archive + 0x8000) & 0xfffffc) << 7) | 0x80000000, 0xf);
    GetBgDataFromArchive(&bg, archive, 0, 0, 0);
    GX_LoadBGPltt(bg.palette->rawData, 0, bg.palette->size);
    GX_LoadBG3Char(bg.character->rawData, 0, bg.character->size);
    GX_LoadBG3Scr(bg.screen->rawData, 0, bg.screen->size);
    NNSi_FndFreeFromDefaultHeap(archive);

    func_ov081_020c5550(state->titleTiles, 1, func_ov081_020c5c04(1), 0x17, 1, 4, 2, 0x3c);
}
