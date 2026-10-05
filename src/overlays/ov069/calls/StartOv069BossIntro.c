#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x9ac];
    u64 flags;
    u8 pad_9b4[0xa51 - 0x9b4];
    s8 dashLevel;
} BossEntity;

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

typedef struct {
    u32 mode : 8;
    u32 step : 8;
    u32 count : 16;
} IntroCounter;

typedef struct {
    u8 pad_00[0x3c];
    int nextState;
    u8 pad_40[0xb0];
    int timer;
    u8 pad_f4[4];
    int seqHandle;
    IntroCounter counter;
} SceneObject;

extern BossEntity *GetBoundedEntryField(int index);
extern void RunHudEnterCallback(void);
extern void ActivateSlotModelGroup(BossEntity *entity, int level);

int StartOv069BossIntro(SceneOwner *owner, SceneObject *obj, int *wait)
{
    BossEntity *entity = GetBoundedEntryField(owner->player);

    entity->flags |= 0x200000000ULL;
    entity->flags |= 0x1000000;
    entity->flags |= 0x20000000;
    RunHudEnterCallback();
    obj->seqHandle = -1;
    obj->timer = 0;
    obj->counter.mode = 0;
    obj->counter.step = 1;
    obj->counter.count = 1;
    entity->dashLevel = 0;
    ActivateSlotModelGroup(entity, entity->dashLevel);
    *wait = 0x18;
    return obj->nextState;
}
