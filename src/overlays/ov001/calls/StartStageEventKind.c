#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AttachPoint {
    u32 key;
    s32 nameIndex;
    u8 pad_08[0xc];
    VecFx32 scale;
} AttachPoint;

typedef struct EventKindInfo {
    u32 action;
    u32 attachKey;
    u32 objectId;
    u32 mirrored;
    s32 duration;
} EventKindInfo;

typedef struct EventKindTable {
    EventKindInfo entries[10];
} EventKindTable;

typedef struct SpawnRequest {
    u16 unk_00;
    u16 objectId;
    u16 unk_04;
    u16 ownerId;
    u16 active : 1;
    u16 mirrored : 1;
    u16 hidden : 1;
    u16 unk_08_3 : 13;
    u16 unk_0a;
    s32 nameIndex;
} SpawnRequest;

typedef struct TargetItem {
    u8 pad_00[0xc];
    s32 target;
} TargetItem;

typedef struct TargetTable {
    u8 pad_00[4];
    u32 count;
    u32 stride;
    u8 *items;
} TargetTable;

typedef struct StageResource {
    u8 pad_00[8];
    TargetTable *table;
} StageResource;

typedef struct StageEntry {
    u8 pad_00[4];
    StageResource *resource;
} StageEntry;

typedef struct StageController {
    u8 pad_00[8];
    u16 flags;
} StageController;

typedef struct StageRecord {
    u8 pad_00[0x80];
    void *cell;
} StageRecord;

typedef struct StageActor {
    u8 pad_000[0x288];
    u16 flags;
    u8 pad_28a[0x298 - 0x28a];
    s32 speed;
    u8 pad_29c[0x2a8 - 0x29c];
    s32 mode;
    u8 pad_2ac[0x2cc - 0x2ac];
    VecFx32 destination;
    u8 pad_2d8[0x334 - 0x2d8];
    s32 target;
    u8 pad_338[0x364 - 0x338];
    s32 motion;
    u8 pad_368[4];
    s32 turnSpeed;
    u8 pad_370[0x39c - 0x370];
    s32 scale;
} StageActor;

typedef struct StageEvent {
    u8 pad_000[0xc];
    u8 kind;
    u8 pad_00d[3];
    u16 actorId;
    u8 pad_012[2];
    s16 entryId;
    u8 pad_016[2];
    u16 auxId;
    u8 pad_01a[0x4c - 0x1a];
    s32 speed;
    u8 pad_050[0x61 - 0x50];
    u8 hasTarget;
    u8 pad_062[0x1a4 - 0x62];
    s32 duration;
    u8 pad_1a8[4];
    s32 elapsed;
    u8 pad_1b0[0x1b8 - 0x1b0];
    u16 slot;
} StageEvent;

extern const EventKindTable data_ov001_0209e554;
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern StageActor *GetStageActor(s16 id);
extern void *GetStageAuxRecord(u16 id);
extern int ReleaseStageSlotEntry(int index, int slot);
extern void ZeroActorSubStruct(void *aux);
extern void func_ov001_02091ae8(StageActor *actor, u32 firstId, u32 secondId, int flags);
extern void FindStageAttachPoint(StageEvent *event, u32 key, AttachPoint *out);
extern u16 FindStageObjectByOwner(u16 slot, u32 owner);
extern StageRecord *GetStageObjectRecord(void);
extern void BindSlotToSourceCell(void *aux, void *cell);
extern u16 SpawnStageObjectActor(StageEvent *event, SpawnRequest *request, int flags);
extern StageController *GetStageController(u16 slot);
extern void func_ov001_020983c4(StageController *controller, s32 value);
extern void ChooseWanderDestination(StageEvent *event, StageActor *actor, VecFx32 *out);
extern void ClearActorMotionState(StageActor *actor);
extern void func_ov001_020925e4(StageEvent *event, int state);
extern StageEntry *GetStageEntry(int id);

static inline u32 GetTargetCount(StageEntry *entry)
{
    u32 count = 0;

    if (entry != NULL && entry->resource != NULL) {
        count = entry->resource->table->count;
    }
    return count;
}

static inline TargetItem *GetTarget(StageEntry *entry, u32 index)
{
    StageResource *resource;
    u32 count;
    u8 *items;

    if (entry == NULL) {
        return NULL;
    }
    resource = entry->resource;
    if (resource == NULL) {
        return NULL;
    }
    count = GetTargetCount(entry);
    items = (u8 *)resource->table->items;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (TargetItem *)(items + index * resource->table->stride);
}

void StartStageEventKind(StageEvent *event, int kind)
{
    s32 objectId;
    void *aux;
    AttachPoint point;
    AttachPoint spawnPoint;
    SpawnRequest request;
    EventKindTable table;
    StageActor *actor;
    EventKindInfo *info;

    actor = GetStageActor(event->actorId);
    aux = GetStageAuxRecord(event->auxId);
    table = data_ov001_0209e554;
    if (actor == NULL) {
        return;
    }
    if (event->slot != 0) {
        ReleaseStageSlotEntry(4, event->slot);
        event->slot = 0;
    }
    ZeroActorSubStruct(aux);
    info = &table.entries[kind];
    event->kind = kind;
    event->duration = info->duration;
    event->elapsed = 0;
    if (actor != NULL) {
        actor->scale = 0x1000;
        actor->speed = event->speed;
        actor->flags = ~0x1000 & actor->flags;
        func_ov001_02091ae8(actor, 0xffff, 0xffff, 0);
    }
    FindStageAttachPoint(event, info->attachKey, &point);
    switch (info->action) {
    case 2:
        FindStageObjectByOwner(info->objectId, 1);
        BindSlotToSourceCell(aux, GetStageObjectRecord()->cell);
        break;
    case 1: {
        u16 mirrored = info->mirrored;
        u32 key;
        u16 slot;
        StageController *controller;

        objectId = info->objectId;
        key = info->attachKey;
        func_01ff88c4(&request, 0, sizeof(SpawnRequest));
        FindStageAttachPoint(event, key, &spawnPoint);
        request.objectId = objectId;
        request.active = 1;
        request.hidden = 0;
        request.ownerId = event->actorId;
        request.nameIndex = spawnPoint.nameIndex;
        request.mirrored = mirrored;
        slot = SpawnStageObjectActor(event, &request, 0);
        controller = GetStageController(slot);
        if (controller != NULL) {
            controller->flags |= 4;
            controller->flags |= 8;
            func_ov001_020983c4(controller, spawnPoint.scale.x);
        }
        event->slot = slot;
        break;
    }
    }
    switch (event->kind) {
    case 5:
        ChooseWanderDestination(event, actor, &actor->destination);
        break;
    case 9:
        actor->motion = 0;
        ClearActorMotionState(actor);
        func_ov001_020925e4(event, 10);
        actor->flags |= 0x1000;
        break;
    case 8:
        actor->motion = 0;
        ClearActorMotionState(actor);
        func_ov001_020925e4(event, 4);
        break;
    case 2:
        actor->motion = 0;
        actor->scale = 0;
        break;
    case 4:
        actor->motion = 0;
        actor->turnSpeed = 0x1800;
        actor->scale = 0;
        actor->speed = 0x80;
        if (event->hasTarget) {
            StageEntry *entry = GetStageEntry(event->entryId);
            if (entry != NULL) {
                TargetItem *item = GetTarget(entry, 0);
                if (item != NULL && item->target != 0) {
                    actor->target = item->target;
                    actor->mode = 0x52;
                }
            }
        }
        break;
    case 6:
        actor->scale = 0x333;
        break;
    case 7:
        actor->scale = 0;
        break;
    }
    if (event->slot != 0) {
        StageController *controller = GetStageController(event->slot);
        if (controller != NULL) {
            func_ov001_020983c4(controller, point.scale.x);
        }
    }
}





