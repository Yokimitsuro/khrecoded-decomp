#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 anim[4];
} BodyModel;

typedef struct {
    u8 pad0[0x230];
    BodyModel *body;
    u8 pad234[0x874 - 0x234];
    u8 stateMachine[0x9ac - 0x874];
    u64 flags;
} Actor;

extern void Flags16_SetBit1(void *anim);
extern void Flags16_ClearBit1(void *anim);
extern void SetPaused(void *obj, int paused);
extern void SetObjectAnimationEnabled(void *obj, int enabled);

void SetActorPaused(Actor *actor, int paused)
{
    int i;
    if (paused) {
        if (!(actor->body->flags & 0x20)) {
            Flags16_SetBit1(actor->body->anim);
        }
        actor->flags |= 0x200;
    } else {
        if (!(actor->body->flags & 0x20)) {
            Flags16_ClearBit1(actor->body->anim);
        }
        actor->flags &= ~(u64)0x200;
    }
    SetPaused(actor->stateMachine, paused);
    for (i = 0; i < 2; i++) {
        SetObjectAnimationEnabled((u8 *)actor + 0xb68 + i * 0x230, paused);
    }
}
