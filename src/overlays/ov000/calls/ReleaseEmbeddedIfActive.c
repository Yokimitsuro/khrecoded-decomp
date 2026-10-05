#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x94];
    u8 node[0x104];
    u32 active;
} Owner;

extern void ReleaseResourceAndDetach(void *node);

void ReleaseEmbeddedIfActive(Owner *owner)
{
    if (owner->active == 0) {
        return;
    }
    ReleaseResourceAndDetach(owner->node);
    owner->active = 0;
}
