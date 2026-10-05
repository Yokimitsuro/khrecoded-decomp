#include "nitro/types.h"

typedef struct MessageWindow {
    u8 pad_00[8];
    int state;
    u8 pad_0c[0x58];
    int hasMorePages;
    u8 pad_68[0x1c];
    u32 waitTickLow;
    u32 waitTickHigh;
} MessageWindow;

extern int *data_ov001_020a04e4;
extern void *GetSceneTagTracker(void);
extern void PlaceWindowCornerTag(MessageWindow *window);
extern void DrawGridMenuCells(MessageWindow *window, u32 flag);
extern u64 OS_GetTick(void);

void FinishMessageWindowPage(MessageWindow *window)
{
    int *mode = data_ov001_020a04e4;
    u64 tick;

    GetSceneTagTracker();
    if (window->hasMorePages == 0) {
        if (*mode != 1) {
            PlaceWindowCornerTag(window);
        }
        window->state = 6;
        return;
    }
    DrawGridMenuCells(window, 0);
    window->state = 5;
    tick = OS_GetTick();
    window->waitTickLow = tick;
    window->waitTickHigh = tick >> 32;
}
