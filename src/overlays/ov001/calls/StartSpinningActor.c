#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpinningActor {
    u8 pad_00[0x14];
    void *update;
    u8 pad_18[0x20];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
    u8 pad_4c[2];
    u16 flags;
    u8 pad_50[8];
    s32 active;
    u16 angle;
    u8 pad_5e[2];
    VecFx32 homePosition;
    u8 pad_6c[4];
    VecFx32 velocity;
    VecFx32 direction;
    fx32 angleRadians;
    s32 timer;
} SpinningActor;

extern const VecFx32 data_0205344c;
extern const s16 data_02053580[];
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void SpawnSoundSlot(int soundId, int arg1, VecFx32 *position, int arg3);
extern void StepFallingObject();

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

void StartSpinningActor(SpinningActor *actor)
{
    int index;

    actor->active = 1;
    actor->update = StepFallingObject;
    actor->position = actor->homePosition;
    actor->velocity = data_0205344c;
    index = actor->angle >> 4;
    actor->direction = MakeVec(data_02053580[(0x400 - index) & 0xfff], 0, data_02053580[index]);
    actor->angleRadians = (s64)actor->angle * 0x6488 / 0x10000;
    actor->timer = 0;
    ActorSlot_SetFlag8ByIndex(actor->actorId, TRUE);
    SpawnSoundSlot(0x1a1, 0, &actor->position, 0);
    actor->flags |= 0x20;
}
