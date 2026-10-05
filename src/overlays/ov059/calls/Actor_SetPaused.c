#include "nitro/types.h"

typedef struct {
    u8 data[0x230];
} ModelSet;

typedef struct {
    u32 flags;
    u8 anim[4];
} BodyModel;

typedef struct {
    u8 pad_000[0x230];
    BodyModel *body;
    u8 pad_234[0x928 - 0x234];
    u64 flags;
    u8 pad_930[0x9d4 - 0x930];
    ModelSet modelSets[2];
} Actor;

extern void Flags16_SetBit1(void *anim);
extern void Flags16_ClearBit1(void *anim);
extern void SetObjectAnimationEnabled(void *obj, int enabled);

void Actor_SetPaused(Actor *actor, int paused)
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
    for (i = 0; i < 2; i++) {
        SetObjectAnimationEnabled(&actor->modelSets[i], paused);
    }
}
