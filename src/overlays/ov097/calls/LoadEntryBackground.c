#include "nitro/types.h"

typedef struct {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

typedef struct {
    void *fileData;
    BgGraphicsData bg;
} GraphicsResource;

typedef struct {
    u8 pad_00[0x30];
    u32 bgFileIndex;
} MenuEntryDef;

typedef struct {
    int entryIndex;
    u8 pad_004[0x14];
    u32 archiveBase;
    u8 pad_01c[0x124];
    GraphicsResource resources[4];
    u8 pad_180[4];
    int listMode;
} MenuScene;

#define ARCHIVE_FILE(base, index) ((((base) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

extern MenuEntryDef data_ov097_020c2144[];
extern BOOL IsEntryFlagSet_020c1494(int flagSet, int entryIndex);
extern void *Archive_LoadFile(u32 fileId, int heapId);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void DispatchByPartType(int part, void *screen, void *character, void *palette, int arg4, int arg5);

void LoadEntryBackground(MenuScene *scene)
{
    GraphicsResource *resource;
    MenuEntryDef *entry;
    u32 planes;

    if (scene->listMode == 1 && !IsEntryFlagSet_020c1494(0, 0)) {
        planes = (*(vu32 *)0x04001000 & 0x1f00) >> 8;
        *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | ((planes & ~1) << 8);
    }
    resource = &scene->resources[1];
    entry = &data_ov097_020c2144[scene->entryIndex];
    resource->fileData = Archive_LoadFile(ARCHIVE_FILE(scene->archiveBase, entry->bgFileIndex & 0x1ff), 0xe);
    GetBgDataFromArchive(&resource->bg, resource->fileData, 0, 0, 0);
    DispatchByPartType(4, resource->bg.screen, resource->bg.character, resource->bg.palette, 0x1d, 2);
}
