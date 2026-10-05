#include "nitro/types.h"

typedef struct CharacterData {
    u32 pad_00;
    u32 width;
    u32 height;
    u32 pad_0c;
    u32 format;
} CharacterData;

typedef struct PaletteData {
    int fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void *pRawData;
} PaletteData;

typedef struct ImageInfo {
    u32 format;
    u32 width;
    u32 height;
    void *cellBank;
    void *animBank;
} ImageInfo;

typedef struct DispObjImage {
    u32 pad_00;
    ImageInfo info;
    void *cellFile;
    void *animFile;
    void *archive;
    u8 paletteProxy[0x14];
    u8 imageProxy[0x24];
    u32 blockCount;
    u8 pad_60[4];
    s16 paletteSlot;
} DispObjImage;

typedef struct DispManager {
    u8 pad_0000[0x4612];
    u16 paletteFlags;
    u8 pad_4614[2];
    u16 paletteOffset;
    u8 pad_4618[0x6020 - 0x4618];
    BOOL useAltLoader;
} DispManager;

extern int DecodeStateAt4604(DispManager *manager);
extern void *Archive_LoadFile(int fileId, int kind);
extern void *func_0202c4a0(int fileId, int kind);
extern void func_0202d328(void *archive, int mode);
extern void *NestedPointer_GetFirstWord(void *archive, int index, int arg);
extern BOOL NNS_G2dGetUnpackedCharacterData(void *file, CharacterData **out);
extern u32 FindFreeVramGapOffset(DispManager *manager, CharacterData *data);
extern void NNS_G2dLoadImage1DMapping(CharacterData *data, u32 offset, int vramType, void *proxy);
extern BOOL NNS_G2dGetUnpackedCellBank(void *file, void **out);
extern BOOL NNS_G2dGetUnpackedAnimBank(void *file, void **out);
extern u32 DispObj_GetCharBlockCount(DispManager *manager, DispObjImage *image);
extern BOOL NNS_G2dGetUnpackedPaletteData(void *file, PaletteData **out);
extern int FindFirstClearFlag(DispManager *manager);
extern void NNS_G2dLoadPalette(PaletteData *data, u32 addr, int vramType, void *proxy);

void DispObj_LoadImage(DispManager *manager, int fileId, DispObjImage *image)
{
    CharacterData *charData;
    PaletteData *palette;
    void *archive;
    void *paletteFile;
    void *charFile;
    int vramType;
    ImageInfo *info = &image->info;

    DecodeStateAt4604(manager);
    if (manager->useAltLoader) {
        archive = func_0202c4a0(fileId, 0xe);
    } else {
        archive = Archive_LoadFile(fileId, 0xe);
    }
    image->archive = archive;
    func_0202d328(archive, 1);
    vramType = DecodeStateAt4604(manager);
    if (vramType == 0) {
        charFile = NestedPointer_GetFirstWord(archive, 2, 0);
    } else {
        charFile = NestedPointer_GetFirstWord(archive, 1, 0);
    }
    NNS_G2dGetUnpackedCharacterData(charFile, &charData);
    image->info.format = charData->format;
    image->info.width = charData->width;
    image->info.height = charData->height;
    NNS_G2dLoadImage1DMapping(charData, FindFreeVramGapOffset(manager, charData), vramType, image->imageProxy);
    image->cellFile = NestedPointer_GetFirstWord(archive, 3, 0);
    image->animFile = NestedPointer_GetFirstWord(archive, 5, 0);
    NNS_G2dGetUnpackedCellBank(image->cellFile, &info->cellBank);
    NNS_G2dGetUnpackedAnimBank(image->animFile, &info->animBank);
    image->blockCount = DispObj_GetCharBlockCount(manager, image);
    image->paletteSlot = -1;
    paletteFile = NestedPointer_GetFirstWord(archive, 0, 0);
    if (paletteFile != NULL) {
        NNS_G2dGetUnpackedPaletteData(paletteFile, &palette);
        if (palette->bExtendedPlt) {
            palette->szByte = 0x200;
            image->paletteSlot = FindFirstClearFlag(manager);
            manager->paletteFlags |= (u16)(1 << image->paletteSlot);
            NNS_G2dLoadPalette(palette, image->paletteSlot << 9, vramType, image->paletteProxy);
        } else {
            NNS_G2dLoadPalette(palette, manager->paletteOffset, vramType, image->paletteProxy);
            manager->paletteOffset += palette->szByte;
        }
    }
}
