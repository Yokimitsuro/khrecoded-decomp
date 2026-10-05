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
extern u8 *func_ov001_0209c114(u32 id);
extern void func_ov001_0209473c(u8 *eventRecord);

void UpdateActorStageEvent(ControllerOwner *owner)
{
    ControlledActor *actor = GetStageActor(owner->actorId);
    u8 *eventRecord;

    if (actor != NULL && actor->controlData != NULL && func_ov001_0209c5ac(0x40000000) == 0 &&
        actor->controlMode == 1) {
        eventRecord = func_ov001_0209c114(actor->controllerIndex);
        if (eventRecord != NULL) {
            func_ov001_0209473c(eventRecord);
        }
    }
}
