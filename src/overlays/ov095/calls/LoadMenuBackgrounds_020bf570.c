#include "nitro/types.h"

typedef struct ScreenData {
    u16 width;
    u16 height;
} ScreenData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
} CharacterData;

typedef struct BgGraphicsData {
    ScreenData *screen;
    CharacterData *character;
    void *palette;
} BgGraphicsData;

typedef struct {
    int ids[7];
} TileIdList7;

typedef struct {
    int ids[2];
} TileIdList2;

typedef struct {
    u8 pad_000[8];
    u32 archiveBase;
    u32 sharedArchiveBase;
    u8 pad_010[0x120];
    void *frameArchive;
    BgGraphicsData frameBg;
    void *panelArchive;
    BgGraphicsData panelBg;
    void *tabArchive;
    BgGraphicsData tabBg;
    void *overlayArchive;
    BgGraphicsData overlayBg;
    void *sharedArchive;
    BgGraphicsData sharedBg;
} MenuBgScene;

#define ARCHIVE_FILE(base, index) ((((base) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

extern TileIdList7 data_ov095_020c1728;
extern TileIdList2 data_ov095_020c1714;
extern void *Archive_LoadFile(u32 fileId, int heapId);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void DispatchByPartType(int part, void *screen, void *character, void *palette, int arg4, int arg5);
extern int Gfx_EnqueueTableCmdAt14(int idx, void *p, int arg2, int arg3);
extern void LoadScreenRegion(ScreenData *dst, ScreenData *src, int fromTile, int toTile, int palette, int tile,
                                int width, int height, int stepX, int stepY);

void LoadMenuBackgrounds_020bf570(MenuBgScene *scene)
{
    TileIdList7 panelTiles;
    TileIdList2 tabTiles;
    ScreenData *screen;
    int i;
    int width;
    int height;

    scene->frameArchive = Archive_LoadFile(ARCHIVE_FILE(scene->archiveBase, 0x2e), 0xe);
    GetBgDataFromArchive(&scene->frameBg, scene->frameArchive, 0, 0, 0);
    DispatchByPartType(2, scene->frameBg.screen, scene->frameBg.character, scene->frameBg.palette, 0x1c, 0);

    scene->panelArchive = Archive_LoadFile(ARCHIVE_FILE(scene->archiveBase, 0x2f), 0xe);
    GetBgDataFromArchive(&scene->panelBg, scene->panelArchive, 0, 0, 0);
    screen = scene->panelBg.screen;
    width = (u32)screen->width >> 3;
    height = (u32)screen->height >> 3;
    panelTiles = data_ov095_020c1728;
    for (i = 0; i < 7; i++) {
        LoadScreenRegion(screen, screen, 0xd, panelTiles.ids[i], 0xe, panelTiles.ids[i], width, height, 3, 3);
    }
    DispatchByPartType(3, scene->panelBg.screen, scene->panelBg.character, scene->panelBg.palette, 0x1e, 0);

    scene->tabArchive = Archive_LoadFile(ARCHIVE_FILE(scene->archiveBase, 0x30), 0xe);
    GetBgDataFromArchive(&scene->tabBg, scene->tabArchive, 0, 0, 0);
    {
        ScreenData *tabScreen = scene->tabBg.screen;
        int j;
        int tabWidth = (u32)tabScreen->width >> 3;
        int tabHeight = (u32)tabScreen->height >> 3;

        tabTiles = data_ov095_020c1714;
        for (j = 0; j < 2; j++) {
            LoadScreenRegion(tabScreen, tabScreen, 0xd, tabTiles.ids[j], 0xe, tabTiles.ids[j], tabWidth, tabHeight,
                                3, 3);
        }
    }

    *(vu32 *)0x0400001c = 0x1e00000;

    scene->sharedArchive = Archive_LoadFile(ARCHIVE_FILE(scene->sharedArchiveBase, 0), 0xe);
    GetBgDataFromArchive(&scene->sharedBg, scene->sharedArchive, 0, 0, 0);
    Gfx_EnqueueTableCmdAt14(1, scene->sharedBg.character, 0, scene->sharedBg.character->size);

    scene->overlayArchive = Archive_LoadFile(ARCHIVE_FILE(scene->archiveBase, 0x2c), 0xe);
    GetBgDataFromArchive(&scene->overlayBg, scene->overlayArchive, 0, 0, 0);
    DispatchByPartType(4, scene->overlayBg.screen, scene->overlayBg.character, scene->overlayBg.palette, 0x1f,
                                0);
}












