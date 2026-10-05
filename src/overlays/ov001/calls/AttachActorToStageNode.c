#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageActor StageActor;

typedef struct FieldActor {
    u8 pad_000[0x12a];
    u16 motionFlags;
    u8 pad_12c[0x15c];
    u16 unk_288_0 : 10;
    u16 alignToNode : 1;
    u16 unk_288_11 : 5;
    u8 pad_28a[0x36];
    VecFx32 nodePosition;
    u8 pad_2cc[0xe0];
    s16 attachActorId;
    u16 attachNodeIndex;
} FieldActor;

extern StageActor *GetStageActor(int id);
extern u16 FindActorResourceIndexByName(StageActor *actor, const char *name);
extern void GetNodePosition(StageActor *owner, u32 nodeId, VecFx32 *out);

void AttachActorToStageNode(FieldActor *actor, int stageActorId, const char *nodeName, int align)
{
    StageActor *stageActor;

    if (stageActorId == 0) {
        actor->attachActorId = 0;
        actor->attachNodeIndex = 0;
        actor->alignToNode = 0;
        actor->motionFlags &= 0xffbf;
        return;
    }
    stageActor = GetStageActor((s16)stageActorId);
    if (stageActor != NULL) {
        actor->attachActorId = stageActorId;
        actor->attachNodeIndex = FindActorResourceIndexByName(stageActor, nodeName);
        actor->alignToNode = (u16)align;
        actor->motionFlags |= 0x40;
        GetNodePosition(stageActor, actor->attachNodeIndex, &actor->nodePosition);
    }
}
