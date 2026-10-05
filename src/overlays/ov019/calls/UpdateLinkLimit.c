#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x3c];
    s32 baseLimit;
    u8 pad_40[0x1a];
    u16 flags;
    u8 pad_5c[8];
    s32 limit;
} Actor;

typedef struct LinkDesc {
    u8 kind;
    u8 group;
    u8 index;
} LinkDesc;

typedef struct LinkInfo {
    u8 pad_00[0x194];
    LinkDesc link;
} LinkInfo;

typedef struct Slot {
    s32 limit;
    u8 pad_04[8];
} Slot;

typedef struct Owner {
    u8 pad_00[0x14];
    LinkInfo *info;
    u8 pad_18[0x3c];
    Slot slots[4];
} Owner;

typedef struct Context {
    Owner *owner;
    int mode;
} Context;

extern Actor *func_ov001_0208724c(u32 group, u32 index);

void UpdateLinkLimit(Context *context, void *unused, Actor *actor)
{
    int i;
    if (context->mode == 4) {
        LinkDesc *link = &context->owner->info->link;
        if (link->kind == 4) {
            Actor *linked = func_ov001_0208724c(link->group, link->index);
            if (linked->flags & 1) {
                actor->limit = linked->limit + 0x1800;
                return;
            }
            actor->limit = linked->baseLimit + 0x1800;
            return;
        }
    }
    for (i = 0; i < 4; i++) {
        s32 limit = context->owner->slots[i].limit;
        if (actor->limit < limit) {
            actor->limit = limit;
        }
    }
}
