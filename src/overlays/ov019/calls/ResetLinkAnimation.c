#include "nitro/types.h"

typedef struct ActorNode {
    u8 pad_00[4];
    s16 anim;
} ActorNode;

typedef struct Actor {
    u8 pad_00[0x30];
    u16 renderFlags;
    u8 actorId;
    u8 pad_33[0x47 - 0x33];
    s8 animIndex;
    u8 pad_48[0x5a - 0x48];
    u16 flags;
} Actor;

extern ActorNode *ActorRegistry_GetEntityByIndex(u8 actorId);
extern void Flags16_SetBit1(s16 *anim);
extern void RebindAnimTracks(s16 *anim, int blendIndex, int frame);
extern void SettleLinkHeight(Actor *self, BOOL sweep);
extern void RefreshLeadLinkFlags(Actor *actor);

void ResetLinkAnimation(Actor *self)
{
    self->flags &= 0xfe6f;
    self->animIndex = 0;
    RebindAnimTracks(&ActorRegistry_GetEntityByIndex(self->actorId)->anim, self->animIndex, 0);
    Flags16_SetBit1(&ActorRegistry_GetEntityByIndex(self->actorId)->anim);
    self->renderFlags |= 8;
    if (!(self->flags & 1)) {
        SettleLinkHeight(self, TRUE);
    }
    RefreshLeadLinkFlags(self);
}
