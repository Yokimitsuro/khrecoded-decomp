#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 size;
    void *data;
} PaletteBlock;

typedef struct {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharacterBlock;

typedef struct {
    void *screen;
    CharacterBlock *character;
    PaletteBlock *palette;
} BgGraphicsData;

typedef struct {
    u32 words[5];
} TagTrackerConfig;

extern const TagTrackerConfig data_ov086_020c21dc;
extern u32 BuildSlotImageParams(int slot, u32 low);
extern void *func_0202c4a0(u32 fileId, u32 heapId);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern int NNS_G2dGetUnpackedBGCharacterData(void *file, CharacterBlock **character);
extern void DC_FlushAll(void);
extern void func_ov027_020b7d78(void *tracker, TagTrackerConfig *config);
extern void func_ov027_020b7e44(void *tracker, u32 imageParams);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);

void LoadRecordSubScreenGraphics(u8 *menu)
{
    BgGraphicsData bg;
    TagTrackerConfig config = data_ov086_020c21dc;
    CharacterBlock *character;
    void *file;

    file = func_0202c4a0(BuildSlotImageParams(2, 0x16), 0xe);
    GetBgDataFromArchive(&bg, file, -1, 0, 0);
    GXS_LoadBGPltt(bg.palette->data, 0, bg.palette->size);
    GXS_LoadBG3Char(bg.character->data, 0, bg.character->size);
    NNSi_FndFreeFromDefaultHeap(file);
    file = func_0202c4a0(BuildSlotImageParams(3, 2), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(file, &character);
    DC_FlushAll();
    GXS_LoadBG3Char(character->data, 0, character->size);
    NNSi_FndFreeFromDefaultHeap(file);
    func_ov027_020b7d78(menu + 0x190, &config);
    func_ov027_020b7e44(menu + 0x190, BuildSlotImageParams(2, 0x10));
    func_ov027_020b8230(menu + 0x190, FindActiveRecordById(menu + 0x190, 0x3e8));
}
