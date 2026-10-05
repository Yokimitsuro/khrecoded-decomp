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

extern unsigned int BuildSlotImageParams(int slot, unsigned int low);
extern void *Archive_LoadFile(unsigned int fileId, int flags);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex,
                                          int characterIndex, int paletteIndex);
extern void GX_LoadBGPltt(void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void *UpdateScreenWidgetLayer(int screen);
extern void MIi_CpuCopy16(const void *src, void *dest, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void LoadSlotBgImage(int slot, unsigned int low, int screenIndex, int paletteIndex, void **fileOut)
{
    BgGraphicsData bg;
    void *file = Archive_LoadFile(BuildSlotImageParams(slot, low), 14);
    u32 size;
    void *dest;

    GetBgDataFromArchive(&bg, file, screenIndex, 0, paletteIndex);
    GX_LoadBGPltt(bg.palette->data, 0, bg.palette->size);
    GX_LoadBG3Char(bg.character->data, 0, bg.character->size);
    size = bg.screen->size;
    dest = UpdateScreenWidgetLayer(0xb);
    MIi_CpuCopy16(bg.screen->data, dest, size);
    if (fileOut != 0) {
        *fileOut = file;
        return;
    }
    NNSi_FndFreeFromDefaultHeap(file);
}
