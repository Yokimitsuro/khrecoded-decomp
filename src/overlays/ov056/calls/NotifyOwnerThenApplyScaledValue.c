#include "nitro/types.h"

typedef struct Actor Actor;

typedef struct {
    u8 pad_000[0x200];
    void (*onEvent)(void *owner, u32 eventId);
} OwnerEntity;

extern OwnerEntity *GetBoundedEntryField(u32 handle);
extern void func_ov056_020d4d7c(Actor *actor, u32 handle);

void NotifyOwnerThenApplyScaledValue(Actor *actor, u32 handle)
{
    OwnerEntity *owner = GetBoundedEntryField(handle);

    if (owner->onEvent != NULL) {
        owner->onEvent(owner, 0);
    }
    func_ov056_020d4d7c(actor, handle);
}
