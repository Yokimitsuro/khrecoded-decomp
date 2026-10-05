#include "nitro/types.h"

typedef struct Actor Actor;

typedef struct {
    void (*func)(Actor *actor);
    int id;
    int arg;
} ActorState;

struct Actor {
    u8 pad_000[0x234];
    u32 modeFlags;
    u8 pad_238[0x9ac - 0x238];
    u64 flags;
    u8 pad_9b4[8];
    ActorState state;
};

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

typedef struct {
    u8 pad_00[0x3c];
    int nextState;
    u8 pad_40[0xa4];
    ActorState saved;
    u8 pad_f0[4];
    int phase;
} SceneObject;

extern Actor *GetBoundedEntryField(int index);
extern void RunHudEnterCallback(void);

int StartOv068BossIntro(SceneOwner *owner, SceneObject *obj, int *wait)
{
    Actor *entity = GetBoundedEntryField(owner->player);

    obj->saved = entity->state;
    if (entity->modeFlags & 4) {
        obj->saved.id = 1;
        obj->phase = 4;
    } else {
        obj->saved.id = 4;
        obj->phase = 5;
    }
    RunHudEnterCallback();
    entity->flags |= 0x1000000;
    entity->flags |= 0x20000000;
    entity->flags |= 0x40;
    *wait = 0x18;
    return obj->nextState;
}
