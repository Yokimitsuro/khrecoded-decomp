#include "nitro/types.h"

typedef struct Sequencer Sequencer;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    u8 sequencer[0x9c];
    u32 flags : 31;
    u32 flagTop : 1;
} StageActor;

typedef struct ActorEvent ActorEvent;
typedef void (*ActorEventCallback)(ActorEvent *event, void *arg);

struct ActorEvent {
    u8 pad_000[0xc];
    u8 kind;
    u8 pad_00d[3];
    s16 actorId;
    u16 objectId;
    u8 pad_014[0x1ac];
    ActorEventCallback callback;
    void *callbackArg;
};

extern StageActor *GetStageActor(int id);
extern void *GetStageObjectHandle(u32 id);
extern int SelectSequenceTrack(Sequencer *sequencer, int track);

int FinishActorEventStep(ActorEvent *event)
{
    StageActor *actor = GetStageActor(event->actorId);

    GetStageObjectHandle(event->objectId);
    SelectSequenceTrack((Sequencer *)actor->sequencer, 5);
    if (event->callback != NULL) {
        event->callback(event, event->callbackArg);
    }
    if (event->kind != 9) {
        event->callback = NULL;
        event->callbackArg = NULL;
        actor->flags &= ~0x100;
        return 3;
    }
    actor->flags |= 0x100;
    return 0;
}
