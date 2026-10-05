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
extern void func_ov001_0206c8ec(MenuWindow *window);

void RefreshMenuWindows(void)
{
    MenuWindows *windows = data_ov001_020a04b8;
    int i;

    if (windows == NULL || (windows->flags & 1)) {
        return;
    }
    func_ov001_0206c8ec(&windows->main);
    for (i = 0; i < 3; i++) {
        func_ov001_0206c8ec(&windows->subs[i]);
    }
}
