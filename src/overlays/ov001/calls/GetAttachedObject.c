#include "nitro/types.h"

typedef struct AttachOwner {
    u8 pad_000[0x286];
    u16 attachedId;
} AttachOwner;

extern void *GetStageAttachment(u16 id);

void *GetAttachedObject(AttachOwner *owner)
{
    if (owner == NULL) {
        return NULL;
    }
    if (owner->attachedId == 0) {
        return NULL;
    }
    return GetStageAttachment(owner->attachedId);
}
