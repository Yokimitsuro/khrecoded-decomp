#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x8b8];
    int fadeLevel;
} MoviePlayer;

extern int GetSubtitleStreamFrame(void);
extern void GXx_SetMasterBrightness_(vu16 *brightnessReg, int brightness);

void UpdateMovieFadeOut(MoviePlayer *player) {
    if (player->fadeLevel < 0) {
        if (GetSubtitleStreamFrame() > 0) {
            GXx_SetMasterBrightness_((vu16 *)0x0400006c, 0);
            GXx_SetMasterBrightness_((vu16 *)0x0400106c, 0);
        }
        return;
    }
    if (player->fadeLevel < 16) {
        player->fadeLevel++;
        GXx_SetMasterBrightness_((vu16 *)0x0400006c, -player->fadeLevel);
    }
}
