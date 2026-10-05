#include "nitro/types.h"

typedef struct EventActor {
    u8 pad_000[0x1d0];
    u16 eventMode;
    u16 eventId;
    u8 pad_1D4[0xa4];
    void *eventTarget;
} EventActor;

typedef struct EventTrigger {
    u8 pad_00[0xd];
    u8 actorId;
} EventTrigger;

extern EventActor *GetStageActor(int id);
extern u32 func_ov001_0209c5ac(u32 mask);
extern s32 *func_ov001_0209c114(u32 id);
extern BOOL func_ov001_0209624c(s32 *type);
extern void func_ov001_02093f14(s32 *record);

void TryTriggerActorEvent(EventTrigger *trigger, BOOL busy)
{
    EventActor *actor = GetStageActor(trigger->actorId);
    s32 *record;

    if (actor == NULL || actor->eventTarget == NULL) {
        return;
    }
    if (func_ov001_0209c5ac(1 << 30) != 0 || busy) {
        return;
    }
    if (actor->eventMode != 1) {
        return;
    }
    record = func_ov001_0209c114(actor->eventId);
    if (record == NULL || func_ov001_0209624c(record)) {
        return;
    }
    func_ov001_02093f14(record);
}
