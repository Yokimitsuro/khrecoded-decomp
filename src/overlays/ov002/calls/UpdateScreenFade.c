#include "nitro/types.h"

typedef struct FadeParams {
    u8 direction;
    u8 screens;
    u16 speed;
} FadeParams;

typedef struct FadeState {
    s32 frame;
    FadeParams params;
    s32 brightness;
} FadeState;

extern FadeState *data_ov002_0206c468;
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);

int UpdateScreenFade(void)
{
    BOOL done = FALSE;

    switch (data_ov002_0206c468->params.direction) {
    case 0:
        data_ov002_0206c468->brightness += data_ov002_0206c468->params.speed;
        if (data_ov002_0206c468->brightness > 0) {
            data_ov002_0206c468->brightness = 0;
            done = TRUE;
        }
        break;
    case 1:
        data_ov002_0206c468->brightness -= data_ov002_0206c468->params.speed;
        if (data_ov002_0206c468->brightness < -0x10000) {
            data_ov002_0206c468->brightness = -0x10000;
            done = TRUE;
        }
        break;
    }
    if (data_ov002_0206c468->params.screens & 1) {
        SetBrightnessAndSyncMain(data_ov002_0206c468->brightness >> 12);
    }
    if (data_ov002_0206c468->params.screens & 2) {
        SetSecondaryBrightness(data_ov002_0206c468->brightness >> 12);
    }
    return done ? -2 : 0;
}
