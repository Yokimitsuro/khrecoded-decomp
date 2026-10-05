#include "nitro/types.h"

typedef struct TextWindowEntry {
    u8 data[0x110];
} TextWindowEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x64fc];
    TextWindowEntry windows[3];
    s32 openWindowCount;
    u8 loader[0x1c];
    s32 loaderState;
    u8 pad_6850[0x4c];
    s32 historyEnabled;
    u8 pad_68a0[0x4];
    s32 cooldown;
} OverlayWork;

typedef void (*TextWindowHandler)(TextWindowEntry *window);

extern s32 data_0205fde4;
extern OverlayWork *gTextWindowResourceTable;
extern TextWindowHandler gTextWindowStateHandlers[];
extern void FS_UnloadOverlayImage_0204f5f0(void *loader);
extern int func_ov036_020c280c(TextWindowEntry *window);
extern void PushTextWindowHistory(void);
extern void func_ov036_020bf620(void);

int UpdateTextWindows(void)
{
    OverlayWork *work;
    int i;

    if (data_0205fde4 != 0) {
        return 0;
    }
    if (gTextWindowResourceTable->cooldown > 0) {
        gTextWindowResourceTable->cooldown--;
    }
    FS_UnloadOverlayImage_0204f5f0(gTextWindowResourceTable->loader);
    work = gTextWindowResourceTable;
    if (work->historyEnabled > 0) {
        TextWindowEntry *first = work->windows;

        if (work->loaderState == 1 && func_ov036_020c280c(first) >= 0xd) {
            PushTextWindowHistory();
        }
    }
    for (i = 0; i < 3; i++) {
        TextWindowEntry *window = &gTextWindowResourceTable->windows[i];
        TextWindowHandler handler = gTextWindowStateHandlers[func_ov036_020c280c(window)];

        if (handler != NULL) {
            handler(window);
        }
    }
    func_ov036_020bf620();
    return 0;
}
