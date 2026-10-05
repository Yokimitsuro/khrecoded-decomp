#include "nitro/types.h"

typedef struct ControllerOwner {
    u8 pad_00[0xd];
    u8 actorId;
} ControllerOwner;

typedef struct ControlledActor {
    u8 pad_000[0x1d0];
    u16 controlMode;
    u16 controllerIndex;
    u8 pad_1d4[0x278 - 0x1d4];
    void *controlData;
} ControlledActor;

extern ControlledActor *GetStageActor(s16 actorId);
extern u32 func_ov001_0209c5ac(u32 mask);
extern s32 *GetStageController(u16 index);
extern BOOL IsCommandType4(s32 *type);
extern void FinishStageObjectSpawn(s32 *controller);

void PostUpdateActorController(ControllerOwner *owner)
{
    ControlledActor *actor = GetStageActor(owner->actorId);
    s32 *controller;

    if (actor != NULL && actor->controlData != NULL && func_ov001_0209c5ac(0x40000000) == 0 &&
        actor->controlMode == 2) {
        controller = GetStageController(actor->controllerIndex);
        if (controller != NULL && !IsCommandType4(controller)) {
            FinishStageObjectSpawn(controller);
        }
    }
}
