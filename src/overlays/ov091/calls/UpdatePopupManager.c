#include "nitro/types.h"

typedef struct {
    s32 x;
    s32 y;
    u16 *text;
    s32 param;
} PopupMessage;

typedef struct {
    s32 state;
    u8 pad_04[0x5c];
} PopupWindow;

typedef struct {
    u8 pad_00[0x2c];
    PopupWindow window;
    PopupMessage queue[30];
    s32 queueCount;
} PopupManager;

typedef void (*PopupStateFunc)(PopupWindow *window);

extern PopupManager *data_ov091_020c375c;
extern PopupStateFunc data_ov091_020c2a10[];
extern s32 func_ov091_020c27b4(PopupWindow *window);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void SetPopupState(PopupWindow *window, s32 state);

int UpdatePopupManager(void)
{
    PopupManager *manager = data_ov091_020c375c;
    PopupStateFunc handler = data_ov091_020c2a10[func_ov091_020c27b4(&manager->window)];

    if (handler != NULL) {
        handler(&manager->window);
    }
    if (data_ov091_020c375c->queueCount > 0 && func_ov091_020c27b4(&manager->window) >= 0) {
        MIi_CpuClearFast(0, &data_ov091_020c375c->window, sizeof(PopupWindow));
        SetPopupState(&data_ov091_020c375c->window, 1);
    }
    return 0;
}
