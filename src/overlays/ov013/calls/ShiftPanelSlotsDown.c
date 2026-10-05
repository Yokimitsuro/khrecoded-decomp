#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[2];
    s8 slotCount;
    u8 pad_03[0x254];
    u8 slots[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;

void ShiftPanelSlotsDown(s32 index) {
    while (index < data_ov013_02074ce0->slotCount - 1) {
        if ((index + 1) % 10 == 0) {
            data_ov013_02074ce0->slots[index] = data_ov013_02074ce0->slots[index + 2];
        } else {
            data_ov013_02074ce0->slots[index + 1] = data_ov013_02074ce0->slots[index + 2];
        }
        index++;
    }
}
