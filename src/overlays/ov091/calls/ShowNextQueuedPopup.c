#include "nitro/types.h"

typedef struct {
    s32 x;
    s32 y;
    u16 *text;
    s32 param;
} PopupMessage;

typedef struct {
    s32 state;
    u32 flags;
    s32 stateTimer;
    s32 x;
    s32 y;
    s32 param;
    u8 pad_18[0x34];
    u16 *text;
    u8 pad_50[0x10];
} PopupWindow;

typedef struct {
    u8 pad_00[0x2c];
    PopupWindow window;
    PopupMessage queue[30];
    s32 queueCount;
} PopupManager;

extern PopupManager *data_ov091_020c375c;
extern void SetPopupState(PopupWindow *window, s32 state);
extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);

void ShowNextQueuedPopup(void)
{
    PopupManager *manager = data_ov091_020c375c;

    manager->window.flags = 0;
    manager->window.x = manager->queue[0].x - 0x80;
    manager->window.y = manager->queue[0].y - 0x60;
    manager->window.param = manager->queue[0].param;
    manager->window.text = manager->queue[0].text;
    SetPopupState(&manager->window, 2);
    MIi_CpuCopyFast(&data_ov091_020c375c->queue[1], data_ov091_020c375c->queue,
                             sizeof(data_ov091_020c375c->queue));
    data_ov091_020c375c->queueCount--;
}
