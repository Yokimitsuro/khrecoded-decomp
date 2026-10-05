#include "nitro/types.h"

typedef struct LinkedActor {
    u8 pad_000[0x284];
    u16 firstLinkId;
} LinkedActor;

extern void *GetStageLinkedActor(u16 id);

void *GetFirstLinkedActor(LinkedActor *actor)
{
    if (actor == NULL) {
        return NULL;
    }
    if (actor->firstLinkId == 0) {
        return NULL;
    }
    return GetStageLinkedActor(actor->firstLinkId);
}
