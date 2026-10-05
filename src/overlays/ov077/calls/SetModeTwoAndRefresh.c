#include "nitro/types.h"

typedef struct {
    u8 pad_00000[0xc];
    u32 pending;
    u8 pad_00010[0x11ff4 - 0x10];
    s32 mode;
} MenuWork;

extern void BeginSlotItemSelection(MenuWork *work);
extern void ShowSlotHeaderMessage(MenuWork *work);
extern void *func_ov039_020bc1dc(void);
extern void SetFlagGatedElementsVisible(void *container, BOOL visible);

void SetModeTwoAndRefresh(MenuWork *work)
{
    work->mode = 2;
    if (work->pending != 0) {
        BeginSlotItemSelection(work);
        work->pending = 0;
        return;
    }
    ShowSlotHeaderMessage(work);
    SetFlagGatedElementsVisible(func_ov039_020bc1dc(), TRUE);
}
