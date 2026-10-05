#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SmallRecord {
    u8 pad_00[4];
    s8 effectId;
} SmallRecord;

typedef struct StageActor {
    u8 pad_000[0xB8];
    VecFx32 effectPos;
    u8 pad_0C4[0x1A8];
    u32 stateBits : 31;
    u32 stateTop : 1;
    u8 pad_270[0x50];
    VecFx32 position;
} StageActor;

typedef struct StageEvent {
    u8 pad_00[9];
    u8 kind;
    u8 pad_0A[6];
    u16 actorId;
    u16 objectId;
    u8 pad_14[6];
    u16 recordIndex;
    u8 pad_1C[0x47];
    u8 effectArg;
    u8 pad_64[8];
    u8 soundArg;
    u8 pad_6D[0x2F];
    u32 soundParam;
} StageEvent;

extern u16 *GetStageObjectHandle(u32 id);
extern StageActor *GetStageActor(int id);
extern SmallRecord *GetSmallTableEntry(int index);
extern void func_ov001_02066684(int effectId, VecFx32 *position, u8 arg, int flags);
extern void HandleEnemyDefeat(u16 objectType, u16 recordIndex, VecFx32 *position, u32 param, u8 arg);
extern void FinishScoreEvent(StageEvent *event);

void StartStageEventEffect(StageEvent *event)
{
    u16 *object;
    StageActor *actor;
    SmallRecord *record;

    if (event == NULL || event->actorId == 0) {
        return;
    }
    object = GetStageObjectHandle(event->objectId);
    if (object == NULL) {
        return;
    }
    actor = GetStageActor((s16)event->actorId);
    if (actor == NULL) {
        return;
    }
    if (event->kind != 4 && (actor->stateBits & 1)) {
        return;
    }
    if (event->recordIndex == 0xFFFF) {
        return;
    }
    record = GetSmallTableEntry(event->recordIndex);
    if (record == NULL) {
        return;
    }
    func_ov001_02066684(record->effectId, &actor->effectPos, event->effectArg, 0);
    HandleEnemyDefeat(*object, event->recordIndex, &actor->position, event->soundParam, event->soundArg);
    FinishScoreEvent(event);
}
