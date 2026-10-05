#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x124];
    u32 slotCount;
    u32 slotStride;
    u8 *slots;
} LinkData;

typedef struct {
    u8 pad_00[0x8];
    LinkData *data;
} LinkTarget;

typedef struct {
    u16 id;
    u8 pad_02[2];
    LinkTarget *target;
} StageLink;

typedef struct {
    u8 pad_00[0xe];
    u16 linkId;
    s16 actorIndex;
    u8 pad_12[0x4];
    u16 recordId;
} SlotBinder;

typedef struct SlotTable SlotTable;

extern void *GetStageActor(int index);
extern SlotTable *GetStageMotionRecord(u16 id);
extern StageLink *FindStageLink(u32 id);
extern void SlotTable_Init(SlotTable *table, int which, u32 *data);

static inline u32 GetLinkSlotCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->target == NULL) {
        return 0;
    }
    return link->target->data->slotCount;
}

static inline u32 *GetLinkSlot(StageLink *link, u16 index)
{
    u32 count;
    LinkTarget *target;
    LinkData *data;
    u8 *slots;

    if (link == NULL) {
        return NULL;
    }
    target = link->target;
    if (target == NULL) {
        return NULL;
    }
    count = GetLinkSlotCount(link);
    data = target->data;
    slots = data->slots;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (u32 *)(slots + index * data->slotStride);
}

void BindLinkSlotTable(SlotBinder *binder, u32 which)
{
    SlotTable *table;
    StageLink *link;
    u32 *slotData;

    GetStageActor(binder->actorIndex);
    table = GetStageMotionRecord(binder->recordId);
    link = FindStageLink(binder->linkId);
    if (link == NULL) {
        return;
    }
    slotData = GetLinkSlot(link, 0);
    if (slotData != NULL && which < 2) {
        SlotTable_Init(table, which, slotData);
    }
}
