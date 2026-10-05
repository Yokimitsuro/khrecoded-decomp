#include "nitro/types.h"

extern s32 UpdateMenuSelection(void);
extern s32 IsScreenModeIdle(void);
extern void BeginScreenFadeOut(int flag);

s32 AdvanceCommWhenReady(void)
{
    s32 ready;

    UpdateMenuSelection();
    ready = IsScreenModeIdle();
    if (ready != 0) {
        BeginScreenFadeOut(1);
        return 8;
    }
    return -1;
}
