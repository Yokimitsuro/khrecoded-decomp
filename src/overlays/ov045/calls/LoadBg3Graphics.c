#include "nitro/types.h"

typedef struct {
    u8 pad00[8];
    u32 size;
    void *data;
} PaletteData;

typedef struct {
    u8 pad00[0x10];
    u32 size;
    void *data;
} CharacterData;

typedef struct BgGraphicsData {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GX_LoadBGPltt(void *dest, u32 srcOffset, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern BOOL NNS_G2dGetUnpackedBGCharacterData(void *file, CharacterData **characterOut);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);

void LoadBg3Graphics(void *archive, int characterIndex, int paletteIndex, BOOL loadPalette,
                              void *characterFile, u32 characterOffset)
{
    CharacterData *character;
    BgGraphicsData bg;

    if (!loadPalette) {
        paletteIndex = -1;
    }
    GetBgDataFromArchive(&bg, archive, -1, characterIndex, paletteIndex);
    if (loadPalette) {
        GX_LoadBGPltt(bg.palette->data, 0, bg.palette->size);
    }
    if (characterFile == NULL) {
        GX_LoadBG3Char(bg.character->data, 0, bg.character->size);
        character = bg.character;
    } else {
        NNS_G2dGetUnpackedBGCharacterData(characterFile, &character);
        if (characterIndex >= 0) {
            GX_LoadBG3Char(bg.character->data, 0, bg.character->size);
        }
        GX_LoadBG3Char(character->data, characterOffset, character->size);
    }
    if (archive != NULL) {
        NNSi_FndFreeFromDefaultHeap(archive);
    }
    if (characterFile != NULL) {
        if (characterFile != NULL) {
            NNSi_FndFreeFromDefaultHeap(characterFile);
        }
    }
}

