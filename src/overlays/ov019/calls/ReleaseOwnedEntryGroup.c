#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x64];
    s16 groupId;
} Actor;

void func_ov021_020a8a88(int groupId);

void ReleaseOwnedEntryGroup(Actor *self)
{
    if (self->groupId != -1) {
        func_ov021_020a8a88(self->groupId);
        self->groupId = -1;
    }
}
