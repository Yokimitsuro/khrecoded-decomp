#include "nitro/types.h"

extern void ActorSlot_AddToWorld(void *entry);
extern u8 *data_0206083c;

void TransitionRecordSlot(int index) {
    void **slots = (void **)(data_0206083c + 0x20);
    ActorSlot_AddToWorld(slots[index]);
}
