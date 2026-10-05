#include "nitro/types.h"

typedef struct ScreenImage {
    u32 pad_00[4];
    u32 size;
    void *data;
} ScreenImage;

typedef struct ScreenInfo {
    u8 pad_00[8];
    u16 width;
    u16 height;
} ScreenInfo;

typedef struct ScaledMenu {
    u8 pad_00[0x14];
    u16 *screenData;
    ScreenImage *image;
    u8 pad_1c[4];
    s32 scale;
    BOOL loaded;
    BOOL needsLoad;
    BOOL needsRefresh;
    u8 pad_30[0x48 - 0x30];
    s32 centerX;
    s32 centerY;
    u8 pad_50[8];
    u8 spriteManager[1];
} ScaledMenu;

extern ScaledMenu *data_ov023_020b6f84;
extern ScreenInfo *func_ov001_0207123c(void);
extern void *func_ov027_020b9e10(ScreenInfo *screen, int id);
extern s32 _s32_div_f(s32 numerator, s32 denominator);
extern void GXS_LoadBG3Char(void *data, int offset, u32 size);
extern void NNS_G2dBGLoadScreenRect(void *dst, u16 *src, int srcX, int srcY, int dstX, int dstY, int width, int height, int tilesWide, int tilesHigh);
extern void GXS_LoadBG3Scr(void *tileMap, int offset, int size);
extern void G2x_SetBGyAffine_(void *reg, s32 *matrix, int x, int y, s32 centerX, s32 centerY);
extern void AlarmCallback_0204f140(void *manager);

void RefreshScaledMenuScreen(void)
{
    ScaledMenu *menu = data_ov023_020b6f84;
    ScreenInfo *screen = func_ov001_0207123c();
    void *tileMap = func_ov027_020b9e10(screen, 0x1b);
    s32 matrix[4];
    u16 *screenData;
    u32 tilesWide;
    u32 tilesHigh;

    matrix[0] = _s32_div_f(0x1000, menu->scale);
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = matrix[0];
    if (menu->needsLoad && !menu->loaded) {
        GXS_LoadBG3Char(menu->image->data, 0, menu->image->size);
        screenData = menu->screenData;
        tilesWide = (u32)screenData[0] >> 3;
        tilesHigh = (u32)screenData[1] >> 3;
        NNS_G2dBGLoadScreenRect(tileMap, screenData, 0, 0, 0, 0, screen->width, screen->height, tilesWide, tilesHigh);
        GXS_LoadBG3Scr(tileMap, 0, tilesWide * tilesHigh);
        menu->loaded = TRUE;
    }
    if (menu->needsRefresh) {
        G2x_SetBGyAffine_((void *)0x04001030, matrix, 0, 0, menu->centerX, menu->centerY);
        AlarmCallback_0204f140(menu->spriteManager);
        menu->needsRefresh = FALSE;
    }
}
