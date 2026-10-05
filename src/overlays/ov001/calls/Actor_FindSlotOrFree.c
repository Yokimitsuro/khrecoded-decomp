#include "nitro/types.h"

typedef struct ActorSlot {
    s32 id;
    u8 pad_04[0x24];
} ActorSlot;

typedef struct Actor {
    u8 pad_000[0x718];
    ActorSlot slots[7];
} Actor;

int Actor_FindSlotOrFree(Actor *actor, int id)
{
    int slotIndex;
    int result = -1;

    for (slotIndex = 0; slotIndex < 7; slotIndex++) {
        int slotId = actor->slots[slotIndex].id;
        if (id == slotId) {
            result = slotIndex;
            break;
        }
        if (slotId == -1 && result == -1) {
            result = slotIndex;
        }
    }
    return result;
}
