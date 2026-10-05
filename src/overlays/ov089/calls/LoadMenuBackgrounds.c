#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    u32 size;
    void *rawData;
} CharacterData;

typedef struct {
    u8 pad_00[8];
    u32 size;
    void *rawData;
} PaletteData;

typedef struct {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

extern void *func_ov039_020bc1ac(void);
extern u32 BuildSlotImageParams(int slot, u32 low);
extern void *func_0202c4a0(u32 fileId, int heapId);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern int NNS_G2dGetUnpackedBGCharacterData(void *file, CharacterData **character);
extern void func_ov027_020b7e44(void *pool, u32 params);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);

void LoadMenuBackgrounds(void)
{
    void *pool = func_ov039_020bc1ac();
    void *archive = func_0202c4a0(BuildSlotImageParams(2, 0xf), 0xe);
    CharacterData *character;
    BgGraphicsData bg;

    GetBgDataFromArchive(&bg, archive, -1, 0, 0);
    GX_LoadBGPltt(bg.palette->rawData, 0, bg.palette->size);
    GX_LoadBG3Char(bg.character->rawData, 0, bg.character->size);
    NNSi_FndFreeFromDefaultHeap(archive);
    archive = func_0202c4a0(BuildSlotImageParams(3, 0), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(archive, &character);
    GX_LoadBG3Char(character->rawData, 0x6000, character->size);
    NNSi_FndFreeFromDefaultHeap(archive);
    func_ov027_020b7e44(pool, BuildSlotImageParams(2, 0xe));
    func_ov027_020b8230(pool, FindActiveRecordById(pool, 0));
}
