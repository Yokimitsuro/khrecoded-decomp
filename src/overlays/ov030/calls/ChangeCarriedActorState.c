#include "nitro/types.h"

typedef struct Actor Actor;
typedef int (*ActorHandler)(Actor *actor);

typedef struct {
    ActorHandler handler;
    s32 state;
    s32 timer;
} ActorStateSlot;

typedef struct {
    u8 pad_00[4];
    s32 speed;
    u8 pad_08[4];
    s32 weight;
    u8 pad_10[0xc];
    s16 angle;
    u8 pad_1e[0x16];
    s32 velocity;
    s32 accel;
    s8 targetA;
    u8 pad_3d;
    s8 targetB;
    u8 active;
} ActorMotion;

struct Actor {
    u8 pad_000[0x9ac];
    u64 stateFlags;
    u8 pad_9b4[8];
    ActorStateSlot slot;
    u8 pad_9c8[0xa10 - 0x9c8];
    ActorMotion motion;
};

extern int UpdateDraggedActorState(Actor *actor);
extern int ExitActorState(Actor *actor, int state, int force);
extern int func_ov052_020cd358(Actor *actor, int state);

int ChangeCarriedActorState(Actor *actor, int state)
{
    int result;
    ActorStateSlot *slot = &actor->slot;

    result = slot->state;

    if (state == 1) {
        if (ExitActorState(actor, state, 0) == 0) {
            ActorMotion *motion;

            result = 1;
            slot->handler = UpdateDraggedActorState;
            slot->timer = 0;
            slot->state = result;
            motion = &actor->motion;
            motion->targetB = -1;
            motion->targetA = -1;
            motion->speed = 0x333;
            motion->weight = 0x80;
            motion->angle = 0xc00;
            motion->active = 0;
            motion->velocity = 0;
            motion->accel = 0;
            actor->stateFlags &= ~0x100ULL;
            actor->stateFlags &= ~0x2000000ULL;
            actor->stateFlags &= ~0x8008000ULL;
        }
    } else {
        result = func_ov052_020cd358(actor, state);
    }
    return result;
}

