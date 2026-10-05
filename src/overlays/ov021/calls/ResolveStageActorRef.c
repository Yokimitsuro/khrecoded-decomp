#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1d2];
    u16 eventBase;
} StageActor;

typedef struct {
    u8 pad_00[0x10];
    u16 actorId;
} StageEventRecord;

typedef struct {
    void *actor;
    u32 pad_04;
    StageActor *target;
} StageGlobals;

extern StageGlobals data_ov021_020b56c4;
extern StageEventRecord *GetStageEventRecord(u16 eventId);
extern StageActor *GetStageActor(s16 actorId);
extern StageActor *FindStageObjectById(u16 id);
extern StageActor *GetLinkedStageActor(StageActor *actor);

StageActor *ResolveStageActorRef(void *context, int ref)
{
    StageActor *actor = data_ov021_020b56c4.target;
    StageActor *cur;
    StageEventRecord *record;
    u16 eventId;
    u16 depth;

    if (ref > 0) {
        switch (ref & 0xff00) {
        case 0:
            eventId = actor->eventBase + ref;
            if (eventId != 0) {
                record = GetStageEventRecord(eventId);
                if (record == NULL) {
                    return NULL;
                }
                if (record->actorId == 0) {
                    return NULL;
                }
                actor = GetStageActor(record->actorId);
                if (actor == NULL) {
                    return NULL;
                }
            }
            break;
        case 0xf00:
        case 0xff00:
            actor = FindStageObjectById(ref);
            if (actor == NULL) {
                actor = NULL;
            }
            break;
        }
    } else if (ref <= 0) {
        cur = actor;
        depth = 0;
        if (actor != NULL) {
            do {
                if (depth == (ref < 0 ? -ref : ref)) {
                    return cur;
                }
                cur = GetLinkedStageActor(cur);
                depth++;
            } while (cur != NULL);
        }
    }
    return actor;
}
