#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    u32 size;
} CharacterData;

typedef struct {
    void *screen;
    CharacterData *character;
    void *palette;
} BgGraphicsData;

typedef struct {
    void *fileData;
    BgGraphicsData bg;
} GraphicsResource;

typedef struct {
    u8 pad_000[0x18];
    u32 archiveBase;
    u32 sharedArchiveBase;
    u8 pad_020[0x120];
    GraphicsResource resources[4];
} MenuScene;

#define ARCHIVE_FILE(base, index) ((((base) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

extern void *Archive_LoadFile(u32 fileId, int heapId);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void DispatchByPartType(int part, void *screen, void *character, void *palette, int arg4, int arg5);
extern int Gfx_EnqueueTableCmdAt14(int idx, void *p, int arg2, int arg3);

void LoadMenuGraphics_020bf734(MenuScene *scene)
{
    scene->resources[0].fileData = Archive_LoadFile(ARCHIVE_FILE(scene->archiveBase, 9), 0xe);
    GetBgDataFromArchive(&scene->resources[0].bg, scene->resources[0].fileData, 0, 0, 0);
    DispatchByPartType(4, scene->resources[0].bg.screen, scene->resources[0].bg.character,
                                scene->resources[0].bg.palette, 0x1f, 0);

    scene->resources[3].fileData = Archive_LoadFile(ARCHIVE_FILE(scene->sharedArchiveBase, 0), 0xe);
    GetBgDataFromArchive(&scene->resources[3].bg, scene->resources[3].fileData, 0, 0, 0);
    Gfx_EnqueueTableCmdAt14(4, scene->resources[3].bg.character, 0xc00,
                                     scene->resources[3].bg.character->size);

    scene->resources[2].fileData = Archive_LoadFile(ARCHIVE_FILE(scene->archiveBase, 7), 0xe);
    GetBgDataFromArchive(&scene->resources[2].bg, scene->resources[2].fileData, 0, 0, 0);
    DispatchByPartType(2, scene->resources[2].bg.screen, scene->resources[2].bg.character,
                                scene->resources[2].bg.palette, 0x1f, 0);
}
