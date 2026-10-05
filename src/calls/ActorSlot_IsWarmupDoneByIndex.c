#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[0x1bc];
    s8 warmupTimer;
} ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern ActorRegistry *data_0206083c;

BOOL ActorSlot_IsWarmupDoneByIndex(int index)
{
    BOOL warmingUp = FALSE;
    ActorSlot *slot = data_0206083c->slots[index];

    if ((slot->flags & 0x1000) && slot->warmupTimer < 15) {
        warmingUp = TRUE;
    }
    return !warmingUp;
}
