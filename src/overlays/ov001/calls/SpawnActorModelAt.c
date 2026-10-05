#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 angle;
    u8 pad_82[0xf2];
    u8 savedState[8];
} ModelActor;

typedef struct {
    ModelActor *actor;
    u8 pad_04[0x36];
    u16 frame;
} ModelHolder;

typedef struct {
    u8 pad_000[0xd18];
    ModelHolder *holder;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 busy;
    u32 currentAngle;
    u32 targetAngle;
} ModelOwner;

extern const VecFx32 data_0205344c;
extern void *GetActorRegistry(void);
extern ModelActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void InitTrackingState(ModelHolder *holder, ModelActor *actor);
extern int ProjectPositionDownward(void *map, int ground, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void Obj_SetPosition(ModelActor *actor, const VecFx32 *position);
extern void ActorObject_Reset(ModelOwner *owner, s32 actorId);

void SpawnActorModelAt(ModelOwner *owner, int ground, const VecFx32 *offset, u32 actorId)
{
    VecFx32 position = data_0205344c;
    void *map = GetActorRegistry();
    ModelActor *actor = ActorRegistry_GetEntityByIndex((u16)actorId);
    u8 saved[8];
    ModelActor *model;
    u16 angle;

    if (owner->busy == 0) {
        if (owner->holder == 0) {
            owner->holder = NNSi_FndAllocFromDefaultHeap(0x464);
            MI_CpuFill8(owner->holder, 0, 0x464);
        }
        MI_CpuCopy8(actor->savedState, saved, sizeof(saved));
        InitTrackingState(owner->holder, actor);
        owner->holder->frame = 0;
        MI_CpuCopy8(saved, actor->savedState, sizeof(saved));
        if (ground != 0) {
            ProjectPositionDownward(map, ground, &position);
        }
        VEC_Add(&position, offset, &position);
        Obj_SetPosition(owner->holder->actor, &position);
        angle = owner->holder->actor->angle;
        owner->targetAngle = angle;
        owner->currentAngle = angle;
        model = owner->holder->actor;
        if (!(model->flags & 0x20)) {
            model->angle = angle;
            model->animFlags |= 0x20;
        }
        ActorObject_Reset(owner, actorId);
    }
}
