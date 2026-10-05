#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x258];
    u8 slotPending[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern int DispatchContextCommand(u32 command, int value, int extra, void *buffer);

void RecordPanelClear(int index) {
    int stage;
    int rollover;

    stage = index + 1;
    rollover = stage % 10;
    if (rollover != 0) {
        DispatchContextCommand(0x8000000f, 1, index - stage / 10, NULL);
    } else {
        DispatchContextCommand(0x8000000b, 1, stage, NULL);
    }
    data_ov013_02074ce0->slotPending[index] = 0;
    if (DispatchContextCommand(7, 0, 0, NULL) < index + 1) {
        int tier;
        DispatchContextCommand(0x80000007, index + 1, 0, NULL);
        tier = (index + 1) / 10;
        if (tier > DispatchContextCommand(6, 0, 0, NULL)) {
            DispatchContextCommand(0x80000006, tier, 0, NULL);
        }
    }
    if (DispatchContextCommand(5, 0, 0, NULL) != 0) {
        DispatchContextCommand(0x80000005, 0, 0, NULL);
    }
    if (rollover != 0) {
        DispatchContextCommand(0x80000010, 0, index - (index + 1) / 10, NULL);
    }
}
