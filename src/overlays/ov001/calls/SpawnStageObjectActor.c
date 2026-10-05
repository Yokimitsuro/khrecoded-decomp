#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpawnParams {
    u16 walkerKind;
    u16 ownerSlot;
    u16 spawnArg;
    u16 attachActorId;
    u16 attach : 1;
    u16 align : 1;
    u16 attachDefault : 1;
    u16 unused : 13;
    u16 pad_0a;
    const char *nodeName;
} SpawnParams;

typedef struct SpawnRequest {
    u8 pad_00[0xa];
    u16 row;
    s16 actorId;
} SpawnRequest;

typedef struct SpawnedActor {
    u8 pad_000[0x270];
    u16 spawnArg;
    u8 pad_272[0x280 - 0x272];
    u16 walkerKind;
    u8 pad_282[0x2c0 - 0x282];
    VecFx32 position;
} SpawnedActor;

extern char data_ov001_020a0314[];
extern void WarpWalkerTo(SpawnedActor *walker, const VecFx32 *position);
extern void AttachActorToStageNode(SpawnedActor *actor, int stageActorId, const char *nodeName, int align);
extern int InitStageSpawnRequest(SpawnRequest *request, int type, int arg);
extern u16 FindStageObjectByOwner(u16 slot, u32 owner);
extern int ReleaseStageSlot(int index);
extern SpawnedActor *GetStageActor(int id);
extern SpawnRequest *GetStageController(void);
extern u16 GetStageRowIndex(void);

int SpawnStageObjectActor(int assignRow, SpawnParams *params, VecFx32 *position)
{
    u16 object = FindStageObjectByOwner(params->ownerSlot, 1);
    int slot;
    SpawnRequest *request;
    SpawnedActor *actor;

    if (object == 0) {
        return 0;
    }
    slot = ReleaseStageSlot(4);
    request = GetStageController();
    InitStageSpawnRequest(request, (s16)object, params->spawnArg);
    actor = GetStageActor(request->actorId);
    if (actor == NULL) {
        return 0;
    }
    actor->spawnArg = params->spawnArg;
    if (assignRow) {
        request->row = GetStageRowIndex();
    }
    if (position != NULL) {
        actor->position = *position;
    }
    if (params->attach && params->attachActorId != 0) {
        AttachActorToStageNode(actor, params->attachActorId, params->nodeName, params->align);
    }
    if (params->attach && params->attachDefault) {
        AttachActorToStageNode(actor, 0, data_ov001_020a0314, 0);
    }
    if (params->walkerKind != 0) {
        actor->walkerKind = params->walkerKind;
    }
    WarpWalkerTo(actor, &actor->position);
    return slot;
}
