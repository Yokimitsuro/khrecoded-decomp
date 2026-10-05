#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 eventKind;
    u16 groupArg;
} LinkSlot;

typedef struct {
    u8 pad_00[0x54];
    u32 slotCount;
    u32 slotStride;
    u8 *slots;
} LinkTable;

typedef struct {
    u8 pad_00[8];
    LinkTable *table;
} LinkData;

typedef struct {
    u32 pad_00;
    LinkData *data;
} StageLink;

typedef struct {
    u8 pad_00[0xe];
    u16 kind;
    u16 actorId;
    u8 pad_12[0xa];
    u16 row;
} StageEvent;

typedef struct {
    u8 pad_00[0xc];
    u16 actorId;
} StageController;

typedef struct {
    u8 pad_000[0x1d0];
    u16 eventMode;
    u16 eventBase;
} FieldPlayer;

typedef struct {
    StageEvent *eventRecord;
    StageController *link;
    FieldPlayer *player;
} FieldContext;

typedef struct {
    u8 pad_000[0x270];
    u16 spawnArg;
} StageActor;

typedef struct {
    u32 tag;
    s32 value;
} TaggedValue;

typedef struct {
    TaggedValue slot;
    TaggedValue spawnArg;
    u8 pad_10[4];
    u32 mode;
    u8 position[8];
} SlotSpawnCommand;

extern FieldContext data_ov021_020b56c4;

extern TaggedValue *ResolveTaggedValueRef(void *context, TaggedValue *value);
extern u16 func_ov021_020b0528(void *context, u32 mode, void *operands, VecFx32 *out, const char **outName);
extern StageLink *func_ov001_020995ac(u32 id);
extern StageEvent *func_ov001_0209c114(u32 id);
extern void ResetActorMotion(StageEvent *record, BOOL keepSpeed);
extern void func_ov001_02094f88(StageEvent *record, int groupArg, int scale, int arg);
extern u16 GetStageRowIndex(StageEvent *record);
extern StageActor *func_ov001_0209c068(int id);
extern void func_ov001_02090f34(StageActor *actor, const VecFx32 *position);
extern void AttachActorToStageNode(StageActor *actor, int stageActorId, const char *nodeName, int align);
extern void func_ov001_0209473c(StageEvent *record);

static inline u32 GetLinkSlotCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->data == NULL) {
        return 0;
    }
    return link->data->table->slotCount;
}

static inline LinkSlot *GetLinkSlot(StageLink *link, u16 index)
{
    u32 count;
    LinkData *data;
    LinkTable *table;
    u8 *slots;
    if (link == NULL) {
        return NULL;
    }
    data = link->data;
    if (data == NULL) {
        return NULL;
    }
    count = GetLinkSlotCount(link);
    table = data->table;
    slots = table->slots;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (LinkSlot *)(slots + index * table->slotStride);
}

s32 ScriptOp_SpawnLinkedSlotEvent(void *context, SlotSpawnCommand *cmd)
{
    TaggedValue *slotRef = ResolveTaggedValueRef(context, &cmd->slot);
    TaggedValue *argRef = ResolveTaggedValueRef(context, &cmd->spawnArg);
    StageEvent *eventRecord = data_ov021_020b56c4.eventRecord;
    StageController *controller = data_ov021_020b56c4.link;
    FieldPlayer *player = data_ov021_020b56c4.player;
    const char *nodeName;
    VecFx32 position;
    u16 flags = func_ov021_020b0528(context, cmd->mode, cmd->position, &position, &nodeName);
    StageLink *link;
    u16 count;
    s32 slot;
    u16 index;
    LinkSlot *entry;
    StageEvent *record;
    StageActor *actor;

    if (player->eventMode != 1) {
        return 0;
    }
    if (player->eventBase == 0) {
        return 0;
    }
    link = func_ov001_020995ac(eventRecord->kind);
    if (link == NULL) {
        return 0;
    }
    count = GetLinkSlotCount(link);
    if (count == 0) {
        return 0;
    }
    slot = slotRef->value;
    if (slot < 0) {
        return 0;
    }
    if (slot > count) {
        return 0;
    }
    if (slot == 0) {
        return 0;
    }
    index = slot - 1;
    entry = GetLinkSlot(link, index);
    if (entry == NULL) {
        return 0;
    }
    record = func_ov001_0209c114((u16)((u16)(player->eventBase - 1 + slot) + 1));
    if (record == NULL) {
        return 0;
    }
    if (record->actorId != 0) {
        return 0;
    }
    if (record->kind != entry->eventKind) {
        return 0;
    }
    ResetActorMotion(record, FALSE);
    func_ov001_02094f88(record, entry->groupArg, 0x1000, 0);
    if (eventRecord != NULL) {
        record->row = GetStageRowIndex(eventRecord);
    }
    actor = func_ov001_0209c068((s16)record->actorId);
    if (actor != NULL) {
        u16 nodeActor = 0;
        if (eventRecord != NULL) {
            nodeActor = eventRecord->actorId;
        }
        if (controller != NULL) {
            nodeActor = controller->actorId;
        }
        func_ov001_02090f34(actor, &position);
        actor->spawnArg = argRef->value;
        if (flags & 0x18) {
            AttachActorToStageNode(actor, nodeActor, nodeName, (flags & 0x10) ? TRUE : FALSE);
        }
    }
    func_ov001_0209473c(record);
    return 0;
}
