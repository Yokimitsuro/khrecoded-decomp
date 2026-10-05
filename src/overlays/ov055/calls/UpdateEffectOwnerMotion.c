#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EffectSource {
    u8 pad_00[0x3d];
    s8 kind;
} EffectSource;

typedef struct EffectTask {
    u8 pad_00[0xc];
    void *request;
    u8 pad_10[0x44 - 0x10];
    int spawnTime;
    u8 pad_48[0x50 - 0x48];
    EffectSource *source;
} EffectTask;

typedef struct ActorCounters {
    u8 pad_00[0x40];
    s8 spawnCount;
} ActorCounters;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1f8];
    void (*onEvent)(Actor *actor, int event, int value);
    u8 pad_1fc[0x234 - 0x1fc];
    u32 moveFlags;
    u8 pad_238[0x75c - 0x238];
    int state;
    int elapsed;
    u8 pad_764[4];
    int finished;
    u8 pad_76c[0x9ac - 0x76c];
    u64 flags;
    u8 pad_9b4[0x9c8 - 0x9b4];
    fx32 posX;
    fx32 posY;
    fx32 posZ;
    u8 pad_9d4[0x9f8 - 0x9d4];
    int timer;
    u8 pad_9fc[0xa10 - 0x9fc];
    ActorCounters counters;
    u8 pad_a51[0x1078 - 0xa51];
    EffectTask *task;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setMode)(Actor *actor, int mode);
};

extern void ComputeRootMotionDelta(Actor *actor, VecFx32 *out);
extern void SpawnUnitProjectile(EffectSource *unit, void *arg, void *request);
extern void SpawnEffectParticle(EffectSource *system, int slot, void *desc);

void UpdateEffectOwnerMotion(Actor *actor)
{
    u32 grounded = actor->moveFlags & 4;
    ActorCounters *counters = &actor->counters;
    VecFx32 delta;
    EffectSource *source;
    EffectTask *task;

    ComputeRootMotionDelta(actor, &delta);
    if (!grounded && actor->state != 0x1f && delta.y != 0) {
        actor->posY = delta.y;
    }
    actor->posX += delta.x;
    actor->posZ += delta.z;
    task = actor->task;
    source = task->source;
    if (actor->elapsed >= task->spawnTime && !(actor->flags & 0x2000)) {
        switch (source->kind) {
        case 0:
            SpawnUnitProjectile(source, 0, task->request);
            break;
        case 4:
            SpawnEffectParticle(source, 2, task->request);
            break;
        }
        actor->flags |= 0x2000;
        counters->spawnCount++;
    }
    if (actor->finished == 0) {
        return;
    }
    actor->timer = 0;
    actor->flags &= ~0x2000ULL;
    if (grounded) {
        if (actor->state != 0x21) {
            actor->setMode(actor, 1);
            if (actor->onEvent != NULL) {
                actor->onEvent(actor, 0, -1);
            }
        } else {
            actor->setMode(actor, 5);
        }
    } else {
        actor->setMode(actor, 4);
    }
}
