#include "nitro/types.h"

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    u8 *rawData;
} CharacterData;

typedef struct PaletteData {
    u8 pad_00[8];
    u32 size;
    void *rawData;
} PaletteData;

typedef struct BgGraphicsData {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct MenuScreen {
    u8 pad_00[0x64e9];
    u8 drawMode;
    u8 pad_64ea[0xa];
    u8 drawState[1];
} MenuScreen;

extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void DC_FlushAll(void);
extern void GXS_LoadBG1Char(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void DispatchDrawCommand(u32 entity, int mode);

void LoadSubBgGraphics(MenuScreen *screen, void *archive)
{
    BgGraphicsData bg;

    GetBgDataFromArchive(&bg, archive, -1, 0, 0);
    DC_FlushAll();
    GXS_LoadBG1Char(bg.character->rawData + 0x1a0, 0x1a0, bg.character->size - 0x1a0);
    GXS_LoadBGPltt(bg.palette->rawData, 0, bg.palette->size);
    DispatchDrawCommand((u32)screen->drawState, screen->drawMode);
}
