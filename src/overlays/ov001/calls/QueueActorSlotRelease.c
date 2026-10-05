#include "nitro/types.h"

typedef struct {
    u8 pad[0x3f08];
    int pendingSlots[5];
} SlotState;

extern SlotState *data_ov001_020a0500;
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);

void QueueActorSlotRelease(int slot) {
    int i;
    for (i = 0; i < 5; i++) {
        if (data_ov001_020a0500->pendingSlots[i] == -1) {
            data_ov001_020a0500->pendingSlots[i] = slot;
            break;
        }
    }
    ActorSlot_SetFlag8ByIndex((u16)slot, FALSE);
}
