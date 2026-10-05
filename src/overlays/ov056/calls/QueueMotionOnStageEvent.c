#include "nitro/types.h"

typedef struct MotionParams {
    u32 words[4];
} MotionParams;

typedef struct MotionEntry {
    void *actor;
    MotionParams params;
    int state;
    int active;
} MotionEntry;

typedef struct MotionQueue {
    MotionEntry entries[9];
    int count;
} MotionQueue;

typedef struct MotionActor {
    u8 pad_000[0x150];
    MotionQueue *queue;
} MotionActor;

typedef struct StageEvent {
    u8 pad_00[8];
    int type;
    u8 pad_0c[0x18 - 0xc];
    u16 recordId;
} StageEvent;

extern const MotionParams data_0205584c;
extern void OrbitActorAroundUnit(void);
extern void func_ov001_02087d9c(u32 id, void *callback, void *userData);

void QueueMotionOnStageEvent(void *source, MotionActor *actor, StageEvent *event)
{
    if (event->type == 4) {
        MotionQueue *queue = actor->queue;
        int index = queue->count;
        if (index < 8) {
            MotionEntry *entry;
            queue->count++;
            entry = &queue->entries[index];
            entry->actor = actor;
            entry->params = data_0205584c;
            entry->state = 0;
            entry->active = 1;
            func_ov001_02087d9c(event->recordId, OrbitActorAroundUnit, entry);
        }
    }
}
