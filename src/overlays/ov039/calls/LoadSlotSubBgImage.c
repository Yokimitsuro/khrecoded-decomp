#include "nitro/types.h"

typedef struct {
    u16 width;
    u16 height;
    u32 pixelFormat;
    u32 mappingType;
    u32 characterFormat;
    u32 size;
    void *data;
} CharacterData;

typedef struct {
    u32 format;
    u32 extended;
    u32 size;
    void *data;
} PaletteData;

typedef struct {
    u16 width;
    u16 height;
    u16 colorMode;
    u16 screenFormat;
    u32 size;
    u8 data[4];
} ScreenData;

typedef struct {
    ScreenData *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

extern int data_ov039_020bea20;
extern unsigned int BuildSlotImageParams(int slot, unsigned int low);
extern void *Archive_LoadFile(unsigned int fileId, int flags);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex,
                                          int characterIndex, int paletteIndex);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void *func_ov027_020b9e10(int layers, int id);
extern void func_ov027_020b9e20(int layers, int id);
extern void MIi_CpuCopy16(const void *src, void *dest, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void LoadSlotSubBgImage(int slot, unsigned int low, int screenIndex, int paletteIndex)
{
    BgGraphicsData bg;
    void *file = Archive_LoadFile(BuildSlotImageParams(slot, low), 14);
    int layers = data_ov039_020bea20 + 0xc9a0;
    u32 size;
    void *dest;

    GetBgDataFromArchive(&bg, file, screenIndex, 0, paletteIndex);
    GXS_LoadBGPltt(bg.palette->data, 0, bg.palette->size);
    GXS_LoadBG3Char(bg.character->data, 0, bg.character->size);
    size = bg.screen->size;
    dest = func_ov027_020b9e10(layers, 0x1b);
    MIi_CpuCopy16(bg.screen->data, dest, size);
    func_ov027_020b9e20(layers, 0x1b);
    NNSi_FndFreeFromDefaultHeap(file);
}
