#include "nitro/types.h"

typedef struct PanelSlot {
    s32 timer;
    s32 mode;
} PanelSlot;

typedef struct PanelState {
    u8 pad_00[0xc];
    u8 pages[0x68];
    PanelSlot slots[2];
    u8 pad_84[0x10];
    s32 selectedSlot;
} PanelState;

extern PanelState *data_0205fe24;
extern u16 data_02060500;
extern void PlaySoundEffect(u32 a, u32 b);
extern void func_020284b0(void *state, int page, int delta);

BOOL ToggleSelectedPanelSlot(void)
{
    PanelState *panel = data_0205fe24;
    int slot;

    if ((data_02060500 & 0x80) || (data_02060500 & 0x40)) {
        PlaySoundEffect(0, 0);
        panel->slots[panel->selectedSlot].mode = 0;
        panel->selectedSlot = (panel->selectedSlot == 0) ? 1 : 0;
        panel->slots[panel->selectedSlot].mode = 1;
        panel->slots[panel->selectedSlot].timer = 0;
        for (slot = 0; slot < 2; slot++) {
            func_020284b0(panel->pages, slot, panel->slots[slot].mode);
        }
        return TRUE;
    }
    return FALSE;
}
