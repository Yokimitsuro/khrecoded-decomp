#include "nitro/types.h"

typedef struct BgGraphicsData {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

extern void func_0202d328(void *archive, int extra);
extern void *NestedPointer_GetFirstWord(void *archive, int recordIndex, int entryIndex);
extern BOOL NNS_G2dGetUnpackedScreenData(void *file, void **screenOut);
extern BOOL NNS_G2dGetUnpackedBGCharacterData(void *file, void **characterOut);
extern BOOL NNS_G2dGetUnpackedPaletteData(void *file, void **paletteOut);

void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                   int paletteIndex)
{
    void *file;

    func_0202d328(archive, 0);

    out->screen = NULL;
    if (screenIndex >= 0 && (file = NestedPointer_GetFirstWord(archive, 6, screenIndex)) != NULL
        && !NNS_G2dGetUnpackedScreenData(file, &out->screen)) {
        out->screen = NULL;
    }

    out->character = NULL;
    if (characterIndex >= 0 && (file = NestedPointer_GetFirstWord(archive, 1, characterIndex)) != NULL
        && !NNS_G2dGetUnpackedBGCharacterData(file, &out->character)) {
        out->character = NULL;
    }

    out->palette = NULL;
    if (paletteIndex >= 0 && (file = NestedPointer_GetFirstWord(archive, 0, paletteIndex)) != NULL
        && !NNS_G2dGetUnpackedPaletteData(file, &out->palette)) {
        out->palette = NULL;
    }
}
