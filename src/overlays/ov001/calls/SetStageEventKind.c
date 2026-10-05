#include "nitro/types.h"

typedef struct StageActor StageActor;

typedef struct StageEvent {
    u8 pad_000[0xc];
    u8 kind;
    u8 pad_00d[3];
    s16 actorId;
    u8 pad_012[0x1a4 - 0x12];
    int progress;
    int speed;
    int elapsed;
} StageEvent;

extern void AddSessionCounter(int index, int amount);
extern void func_ov001_02091ae8(StageActor *actor, u32 firstId, u32 secondId, int flags);
extern void ClearActorGroupFlagsAndNotify(StageEvent *event);
extern StageActor *GetStageActor(int id);
extern StageActor *GetLinkedStageActor(StageActor *actor);

void SetStageEventKind(StageEvent *event, u32 kind)
{
    StageActor *actor;

    if (kind != 0 && event->kind == kind) {
        return;
    }
    event->kind = kind;
    event->progress = 0;
    event->elapsed = 0;
    event->speed = 1;
    if (kind == 2) {
        event->speed = 0x4000;
    }
    if (kind == 9) {
        event->speed = 0x2000;
    }
    if (kind == 4) {
        event->speed = 0x4000;
    }
    if (kind == 9 || kind == 2 || kind == 7 || kind == 4 || kind == 8) {
        ClearActorGroupFlagsAndNotify(event);
    }
    for (actor = GetStageActor(event->actorId); actor != NULL; actor = GetLinkedStageActor(actor)) {
        func_ov001_02091ae8(actor, 0xffff, 0xffff, 0);
    }
    switch (kind) {
    case 1:
        AddSessionCounter(0x15, 1);
        break;
    case 2:
        AddSessionCounter(0x16, 1);
        break;
    case 3:
        AddSessionCounter(0x17, 1);
        break;
    case 4:
        AddSessionCounter(0x18, 1);
        break;
    }
}
