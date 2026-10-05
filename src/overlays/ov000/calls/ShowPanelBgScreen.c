#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct BgGraphicsData {
    NNSG2dScreenData *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} BgGraphicsData;

typedef struct BgScreenPair {
    BgGraphicsData main;
    BgGraphicsData sub;
} BgScreenPair;

typedef struct Panel {
    u8 pad_00[0x1a4];
    BgScreenPair screens[5];
} Panel;

extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Scr(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Char(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Scr(const void *src, u32 offset, u32 size);

void ShowPanelBgScreen(Panel *panel, int screenIndex)
{
    BgGraphicsData *main = &panel->screens[screenIndex].main;
    BgGraphicsData *sub;

    GX_LoadBGPltt(main->palette->pRawData, 0, main->palette->szByte);
    GX_LoadBG1Char(main->character->pRawData, 0, main->character->szByte);
    GX_LoadBG1Scr(main->screen->rawData, 0, main->screen->szByte);

    sub = &panel->screens[screenIndex].sub;
    GXS_LoadBGPltt(sub->palette->pRawData, 0, sub->palette->szByte);
    if (sub->character != NULL && sub->screen != NULL) {
        GXS_LoadBG1Char(sub->character->pRawData, 0, sub->character->szByte);
        GXS_LoadBG1Scr(sub->screen->rawData, 0, sub->screen->szByte);
    }
}
