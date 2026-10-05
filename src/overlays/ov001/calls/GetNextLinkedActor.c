#include "nitro/types.h"

typedef struct LinkedActor {
    u8 pad_000[0xa2];
    u16 nextLinkId;
} LinkedActor;

extern void *GetStageLinkedActor(u16 id);

void *GetNextLinkedActor(LinkedActor *actor)
{
    if (actor == NULL) {
        return NULL;
    }
    if (actor->nextLinkId == 0) {
        return NULL;
    }
    return GetStageLinkedActor(actor->nextLinkId);
}
