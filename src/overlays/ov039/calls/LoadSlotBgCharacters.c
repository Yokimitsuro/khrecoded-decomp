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
    void *screen;
    CharacterData *character;
    void *palette;
} BgGraphicsData;

extern unsigned int BuildSlotImageParams(int slot, unsigned int low);
extern void *Archive_LoadFile(unsigned int fileId, int flags);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex,
                                          int characterIndex, int paletteIndex);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void LoadSlotBgCharacters(int slot, unsigned int low, u32 tile)
{
    BOOL wide;
    void *file;
    BgGraphicsData bg;

    file = Archive_LoadFile(BuildSlotImageParams(slot, low), 14);
    GetBgDataFromArchive(&bg, file, -1, 0, -1);
    wide = FALSE;
    if (bg.character->pixelFormat != 3) {
        wide = TRUE;
    }
    GX_LoadBG3Char(bg.character->data, tile << ((u8)wide + 5), bg.character->size);
    NNSi_FndFreeFromDefaultHeap(file);
}
