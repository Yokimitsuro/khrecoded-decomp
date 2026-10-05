#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x2938];
    u32 slots[29];
} Session;

extern Session *data_ov001_020a0480;

void ClearSessionSlots(void) {
    int slotIndex;
    for (slotIndex = 1; slotIndex < 29; slotIndex++) {
        data_ov001_020a0480->slots[slotIndex] = 0;
    }
}
