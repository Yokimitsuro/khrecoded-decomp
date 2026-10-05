#include "nitro/types.h"

typedef struct PullEntry {
    int state;
    void *source;
    void *actor;
    int active;
} PullEntry;

typedef struct PullQueue {
    PullEntry entries[8];
    int count;
} PullQueue;

typedef struct PullActor {
    u8 pad_000[0x150];
    PullQueue *queue;
} PullActor;

typedef struct StageEvent {
    u8 pad_00[8];
    int type;
    u8 pad_0c[0x18 - 0xc];
    u16 recordId;
} StageEvent;

extern BOOL PullActorTowardTarget(void *event, void *work);
extern void StageRecord_ClearStateIfMatches(u32 id, u32 state);
extern void StageRecord_SetCallback(u32 id, void *callback, void *userData);

void QueuePullOnStageEvent(void *source, PullActor *actor, StageEvent *event)
{
    if (event->type == 4) {
        PullQueue *queue = actor->queue;
        int index = queue->count;
        if (index < 8) {
            PullEntry *entry;
            queue->count++;
            entry = &queue->entries[index];
            entry->source = source;
            entry->actor = actor;
            entry->state = 0;
            entry->active = 1;
            StageRecord_SetCallback(event->recordId, PullActorTowardTarget, entry);
            return;
        }
        StageRecord_ClearStateIfMatches(event->recordId, 9);
    }
}
