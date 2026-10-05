#include "nitro/types.h"

typedef struct MenuWindow {
    u8 data[0x28];
} MenuWindow;

typedef struct MenuWindows {
    u32 flags;
    MenuWindow main;
    MenuWindow subs[3];
} MenuWindows;

extern MenuWindows *data_ov001_020a04b8;
extern void FlushScrolledEntryPosition(MenuWindow *window);

void RefreshMenuWindows(void)
{
    MenuWindows *windows = data_ov001_020a04b8;
    int i;

    if (windows == NULL || (windows->flags & 1)) {
        return;
    }
    FlushScrolledEntryPosition(&windows->main);
    for (i = 0; i < 3; i++) {
        FlushScrolledEntryPosition(&windows->subs[i]);
    }
}
