#include "nitro/types.h"

#define REG_MASTER_BRIGHT ((vu16 *)0x0400006c)

typedef struct {
    u8 pad_0000[0xd1bc];
    BOOL refreshTiles;
    u8 pad_d1c0[0xd1d4 - 0xd1c0];
    int stateFrames;
} SceneWork;

extern int GXx_GetMasterBrightness_(vu16 *reg);
extern void SetSceneState(int state, SceneWork *work);

void WaitForBrightnessReset(SceneWork *work)
{
    int brightness = GXx_GetMasterBrightness_(REG_MASTER_BRIGHT);

    if (work->stateFrames == 0) {
        work->refreshTiles = TRUE;
    }
    work->stateFrames++;
    if (brightness == 0) {
        SetSceneState(2, work);
    }
}
