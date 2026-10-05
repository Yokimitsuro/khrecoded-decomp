#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;
typedef void (*ActorSlotCallback)(ActorSlot *slot, void *argument);

struct ActorSlot {
    ActorSlot *next;
    u8 pad_04[0x1c8];
    ActorSlotCallback callback;
};

typedef struct {
    u8 pad_00[0xc];
    ActorSlot *secondaryHead;
    ActorSlot *secondaryTail;
    ActorSlot *primaryHead;
    ActorSlot *primaryTail;
} ActorRegistry;

extern ActorRegistry *data_0206083c;

void ActorRegistry_ForEachCallback(void *argument)
{
    ActorSlot *slot;

    for (slot = data_0206083c->primaryHead; slot != NULL; slot = slot->next) {
        if (slot->callback != NULL) {
            slot->callback(slot, argument);
        }
    }
    for (slot = data_0206083c->secondaryHead; slot != NULL; slot = slot->next) {
        if (slot->callback != NULL) {
            slot->callback(slot, argument);
        }
    }
}
