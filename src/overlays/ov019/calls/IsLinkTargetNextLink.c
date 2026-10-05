#include "nitro/types.h"

typedef struct Actor Actor;

typedef struct LinkDesc {
    u8 kind;
    u8 group;
    u8 index;
} LinkDesc;

typedef struct LinkInfo {
    u8 pad_00[0x194];
    LinkDesc link;
} LinkInfo;

typedef struct Owner {
    u8 pad_00[0x14];
    LinkInfo *info;
} Owner;

typedef struct Context {
    Owner *owner;
    int mode;
} Context;

extern Actor *func_ov001_0208724c(u32 group, u32 index);
extern Actor *FindLiveNextLink(Actor *actor);

BOOL IsLinkTargetNextLink(Context *context, Actor *actor)
{
    if (context->mode == 4) {
        LinkDesc *link = &context->owner->info->link;
        Actor *linked;
        if (link->kind != 4) {
            return FALSE;
        }
        linked = func_ov001_0208724c(link->group, link->index);
        if (linked != NULL && linked != FindLiveNextLink(actor)) {
            return FALSE;
        }
    }
    return TRUE;
}
