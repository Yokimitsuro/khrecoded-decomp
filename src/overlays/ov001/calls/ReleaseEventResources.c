#include "nitro/types.h"

typedef struct StageActor {
    u8 pad_000[0x3b2];
    u16 nextActorId;
} StageActor;

typedef struct StageEvent {
    u8 pad_00[4];
    u16 active : 1;
    u16 flags4High : 15;
    u16 flags6Low : 13;
    u16 hidden : 1;
    u16 flags6High : 2;
    u8 pad_08[8];
    u16 actorId;
    u8 pad_12[4];
    u16 effectId;
    u16 soundId;
    u8 pad_1a[0x19e];
    u16 slotIds[2];
} StageEvent;

extern int ReleaseStageSlotEntry(int index, int slot);
extern StageActor *GetStageActor(int id);
extern void func_ov001_020925e4(StageEvent *event, int value);

void ReleaseEventResources(StageEvent *event)
{
    u16 i;
    u16 actorId;

    actorId = event->actorId;
    if (actorId == 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        if (event->slotIds[i] != 0) {
            ReleaseStageSlotEntry(4, event->slotIds[i]);
            event->slotIds[i] = 0;
        }
    }
    if (event->effectId != 0) {
        ReleaseStageSlotEntry(8, event->effectId);
    }
    if (event->soundId != 0) {
        ReleaseStageSlotEntry(9, event->soundId);
    }
    while (actorId != 0) {
        StageActor *actor = GetStageActor((s16)actorId);
        u16 next;

        if (actor == NULL) {
            break;
        }
        next = actor->nextActorId;
        ReleaseStageSlotEntry(3, actorId);
        actorId = next;
    }
    event->actorId = 0;
    event->effectId = 0;
    event->soundId = 0;
    event->active = 0;
    event->hidden = 0;
    func_ov001_020925e4(event, 1);
}
