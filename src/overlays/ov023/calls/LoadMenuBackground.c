#include "nitro/types.h"

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *rawData;
} CharacterData;

typedef struct PaletteData {
    u8 pad_00[0x8];
    u32 size;
    u8 *rawData;
} PaletteData;

typedef struct BgGraphicsData {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct MenuFlags {
    u8 pad_00[0x4];
    BOOL backgroundLoaded;
} MenuFlags;

extern MenuFlags *data_ov023_020b6f80;

extern void *func_ov027_020ba1f8(void *resource);
extern void *func_ov001_0207123c(void);
extern void func_ov027_020b9d38(void *target, int mode);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void *func_ov001_0207b21c(void);
extern void MIi_CpuCopy16(const void *src, void *dest, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void func_ov027_020ba200(void *resource, int release);
extern void *GetSceneTagTracker(void);
extern void *FindActiveRecordById(void *pool, int id);
extern void func_ov027_020b8230(void *pool, void *record);
extern void func_ov001_02073030(int enable);

void LoadMenuBackground(void *resource)
{
    void *archive = func_ov027_020ba1f8(resource);
    BgGraphicsData bg;
    void *tracker;

    func_ov027_020b9d38(func_ov001_0207123c(), 0x19);
    GetBgDataFromArchive(&bg, archive, -1, 0, 0);
    {
        u8 *dest = bg.palette->rawData + 0x1c2;
        void *src = func_ov001_0207b21c();

        MIi_CpuCopy16(src, dest, 12);
    }
    GXS_LoadBGPltt(bg.palette->rawData, 0, bg.palette->size);
    GXS_LoadBG2Char(bg.character->rawData, 0, bg.character->size);
    func_ov027_020ba200(resource, 1);
    tracker = GetSceneTagTracker();
    func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 1000));
    func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 1001));
    data_ov023_020b6f80->backgroundLoaded = TRUE;
    func_ov001_02073030(1);
}
