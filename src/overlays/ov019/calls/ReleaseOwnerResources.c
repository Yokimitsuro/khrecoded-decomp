#include "nitro/types.h"

typedef struct Owner {
    u8 pad_00[0x64];
    s16 groupId;
    u8 pad_66[2];
    void *resource;
} Owner;

typedef struct Actor {
    u8 pad_00[4];
    Owner *owner;
    u8 pad_08[0x40];
    void *resource;
} Actor;

void ReleaseResourceAndDetach(void *resource);
void NNSi_FndFreeFromDefaultHeap(void *ptr);
void func_ov021_020a8a88(int groupId);

void ReleaseOwnerResources(Actor *self)
{
    Owner *owner = self->owner;
    if (owner->resource != NULL) {
        ReleaseResourceAndDetach(owner->resource);
        NNSi_FndFreeFromDefaultHeap(owner->resource);
        owner->resource = NULL;
    }
    if (self->resource != NULL) {
        ReleaseResourceAndDetach(self->resource);
        NNSi_FndFreeFromDefaultHeap(self->resource);
        self->resource = NULL;
    }
    if (owner->groupId != -1) {
        func_ov021_020a8a88(owner->groupId);
        owner->groupId = -1;
    }
}
