#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20];
    u32 mode;
    u8 pad_24[0x34];
    u8 objManager[0x6434];
    u32 slotPrimary;
    u32 slotSecondary;
    u32 slotExtra[2];
} ScreenState;

extern int IsHudFlag7Set(void);
extern int IsFieldFlag10Set(void);
extern void SetSlotAnimSequence(void *target, u32 index, u32 value);
extern ScreenState *data_ov023_020b6f84;

void ApplyFormationSlots(int formationType)
{
    ScreenState *state;
    int busy;
    int i;

    state = data_ov023_020b6f84;
    busy = IsHudFlag7Set();
    if ((busy == 0) && (busy = IsFieldFlag10Set(), busy == 0)) {
        if (formationType == 2) {
            state->mode = 2;
            SetSlotAnimSequence(state->objManager, state->slotPrimary, 1);
            SetSlotAnimSequence(state->objManager, state->slotSecondary, 3);
            i = 0;
            do {
                SetSlotAnimSequence(state->objManager, state->slotExtra[i], 5);
                i = i + 1;
            } while (i < 2);
            return;
        }
        state->mode = 1;
        i = 0;
        SetSlotAnimSequence(state->objManager, state->slotPrimary, 0);
        SetSlotAnimSequence(state->objManager, state->slotSecondary, 2);
        do {
            SetSlotAnimSequence(state->objManager, state->slotExtra[i], 4);
            i = i + 1;
        } while (i < 2);
    }
}
