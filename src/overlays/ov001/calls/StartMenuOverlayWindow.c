#include "nitro/types.h"

typedef struct OverlayWindow {
    void *object;
    u8 pad_04[0x2c];
    int state;
    u8 pad_34[0x1c];
    int menuId;
    int menuValue;
    u8 pad_58[0x10];
    u32 flags;
    u8 pad_6C[0x38];
    u8 overlayInfo[0x2c];
    int pendingCount;
    void *descriptor;
    void *pendingValue;
    void *currentValue;
    int fadeState;
} OverlayWindow;

extern void FS_StartOverlay(void *overlay);
extern void *Obj_CreateWithTailWork(void *descriptor, void *userData);
extern int func_02029f6c(void);
extern BOOL func_ov001_0207b3f4(void);
extern void ResetMapMenuScreen(void);
extern void func_ov023_020b6c68(u32 index, u32 value);

void StartMenuOverlayWindow(OverlayWindow *window)
{
    BOOL busy = TRUE;

    if (!(window->flags & 1)) {
        busy = FALSE;
    }
    if (busy) {
        return;
    }
    FS_StartOverlay(window->overlayInfo);
    window->object = Obj_CreateWithTailWork(window->descriptor, NULL);
    window->currentValue = window->pendingValue;
    window->pendingCount = 0;
    window->descriptor = NULL;
    window->fadeState = func_02029f6c();
    if (!func_ov001_0207b3f4()) {
        switch (window->menuId) {
        case -2:
            ResetMapMenuScreen();
            break;
        case -1:
            break;
        default:
            func_ov023_020b6c68(window->menuId, window->menuValue);
            break;
        }
    }
    window->state = 3;
}
