#include "nitro/types.h"

typedef struct ActorStateFlags {
    u32 bits : 31;
    u32 top : 1;
} ActorStateFlags;

typedef struct StageActor {
    u8 pad_000[0x14];
    u8 model[0x26c - 0x14];
    ActorStateFlags flags;
    u8 pad_270[0x27e - 0x270];
    u16 recordId;
    u8 pad_280[0x28c - 0x280];
    u16 lowBits : 3;
    u16 eventArgB : 4;
    u16 eventArgA : 4;
    u16 highBits : 5;
} StageActor;

typedef struct StageObjectRecord {
    u8 pad_000[0x116];
    u8 materials[11];
} StageObjectRecord;

typedef struct StageSpawnState {
    int state;
    u8 pad_04[4];
    u16 lowFlags : 4;
    u16 applyMaterials : 1;
    u16 highFlags : 11;
    u16 eventId;
    s16 actorId;
    u16 polygonBase;
} StageSpawnState;

extern void func_ov001_0208f624(void *model, u32 matId, int polygonId);
extern StageActor *GetStageActor(int id);
extern StageObjectRecord *GetStageObjectRecord(u32 id);
extern u8 *GetStageEventRecord(u32 id);
extern void func_ov001_02090a0c(StageActor *actor, int arg);
extern u32 func_ov001_0209734c(u8 *event, StageActor *actor, int argA, int argB);

void FinishStageObjectSpawn(StageSpawnState *spawn)
{
    StageActor *actor = GetStageActor(spawn->actorId);
    StageObjectRecord *record = GetStageObjectRecord(actor->recordId);
    u8 *event;
    u8 i;

    if (actor == NULL) {
        return;
    }
    if (spawn->applyMaterials && record != NULL) {
        for (i = 0; i < 11; i++) {
            u8 material = record->materials[i];
            if (material == 0xff) {
                break;
            }
            func_ov001_0208f624(actor->model, i, (u8)((spawn->polygonBase + material) % 30));
        }
    }
    func_ov001_02090a0c(actor, 0);
    if (spawn->state == 2 && spawn->eventId != 0 && actor->eventArgA != 0) {
        event = GetStageEventRecord(spawn->eventId);
        if (event != NULL && !(actor->flags.bits & 0x40000)) {
            if ((u16)func_ov001_0209734c(event, actor, actor->eventArgA, actor->eventArgB) & 3) {
                spawn->state = 3;
            }
        }
    }
}
