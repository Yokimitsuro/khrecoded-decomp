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
    u8 pad_1e[0x52];
    s32 commandCount;
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
extern StageLink *FindStageLink(u32 id);
extern StageEvent *GetStageEventRecord(u32 id);
extern void ResetGroupCommandState(StageEvent *record);

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

s32 ScriptOp_ResetLinkedSlotEvent(void *context, TaggedValue *operand)
{
    TaggedValue *slotRef = ResolveTaggedValueRef(context, operand);
    StageEvent *eventRecord = data_ov021_020b56c4.eventRecord;
    FieldPlayer *player = data_ov021_020b56c4.player;
    StageLink *link;
    u16 index;
    s32 slot;
    u16 count;
    LinkSlot *entry;
    StageEvent *record;

    if (player->eventMode != 1) {
        return 0;
    }
    if (player->eventBase == 0) {
        return 0;
    }
    link = FindStageLink(eventRecord->kind);
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
    record = GetStageEventRecord((u16)((u16)(player->eventBase - 1 + slot) + 1));
    if (record == NULL) {
        return 0;
    }
    if (record->actorId == 0) {
        return 0;
    }
    if (record->kind != entry->eventKind) {
        return 0;
    }
    if (record->commandCount <= 0) {
        return 0;
    }
    ResetGroupCommandState(record);
    return 0;
}
