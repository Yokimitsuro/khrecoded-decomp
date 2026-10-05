#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x2c];
    u32 actorId;
    u32 variant;
    u8 pad_34[4];
    u16 seqArcA;
    u16 soundA;
    u8 pad_3c[6];
    u16 seqArcB;
    u16 soundB;
} LaunchDesc;

typedef struct {
    u8 pad_00[0x1f];
    u8 kind;
} LaunchSource;

typedef struct {
    u8 pad_00[0xc];
    s16 actorId;
} StageController;

extern u32 data_ov001_0209e478[];
extern void PlayChosenStageSound(VecFx32 *position, s32 seqArcA, s32 soundA, s32 seqArcB, u16 soundB, BOOL useFirst);
extern int SpawnActorById(int linkOwner, int id, int variant);
extern StageController *GetStageController(u32 id);
extern void *GetStageActor(int id);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void WarpWalkerTo(void *actor, VecFx32 *position);
extern void func_ov001_02090308(void *actor);

void SpawnLaunchedActor(int linkOwner, u8 *stage, LaunchDesc *desc, LaunchSource *source, const VecFx32 *velocity, const VecFx32 *origin, BOOL useFirst, BOOL silent)
{
    u32 kind = 0;
    VecFx32 direction;
    VecFx32 target;
    u16 actorId;
    u16 variant;
    StageController *controller;
    void *actor;
    fx32 speed;
    int spawned;

    if (desc == 0 || velocity == 0) {
        return;
    }
    direction = *velocity;
    if (source != 0) {
        kind = source->kind;
    }
    if (kind >= 5) {
        return;
    }
    actorId = desc->actorId;
    variant = desc->variant;
    if (kind != 0) {
        actorId = data_ov001_0209e478[kind];
        variant = 0;
    }
    if (!silent) {
        PlayChosenStageSound((VecFx32 *)(stage + 0x2c0), desc->seqArcA, desc->soundA, desc->seqArcB, desc->soundB, useFirst);
    }
    if (desc->actorId == 0) {
        return;
    }
    spawned = SpawnActorById(linkOwner, actorId, variant);
    if (spawned == 0) {
        return;
    }
    controller = GetStageController(spawned);
    if (controller == 0) {
        return;
    }
    actor = GetStageActor(controller->actorId);
    if (actor == 0) {
        return;
    }
    speed = VEC_Mag(&direction) >> 1;
    if (speed > 4) {
        func_01ffaff4(&direction, &direction);
        if (speed > 0x19a) {
            speed = 0x19a;
        }
    }
    VEC_MultAdd(speed, &direction, origin, &target);
    WarpWalkerTo(actor, &target);
    func_ov001_02090308(actor);
}

