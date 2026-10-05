#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventSide {
    s8 defIndex;
    u8 count;
    u8 pad_02[2];
} EventSide;

typedef struct EventGroup {
    s8 sideCount;
    u8 pad_01[3];
    EventSide sides[1];
} EventGroup;

typedef struct EventDef {
    u8 pad_00[3];
    u8 unk_03_lo : 4;
    u8 spawnLimit : 4;
    u8 pad_04[8];
} EventDef;

typedef struct EventGroupTable {
    u8 pad_00[4];
    EventDef *defs;
    u8 pad_08[4];
    EventGroup *groups[1];
} EventGroupTable;

typedef void (*MotionHandler)(void *motion, VecFx32 *origin, VecFx32 *target);

typedef struct StageState {
    u8 pad_00000[0x18da0];
    u8 spawnCounts[0x58];
    EventGroupTable *eventGroups;
    u8 pad_18dfc[0x18f4c - 0x18dfc];
    MotionHandler motionHandlers[2];
} StageState;

typedef struct LargeTableEntry {
    u8 groupIndex;
    u8 pad_01[2];
    u8 formation;
    fx32 spacing;
} LargeTableEntry;

typedef struct StageEventRecord {
    u8 pad_00[0x6];
    u16 flagsLow : 7;
    u16 hidden : 1;
    u16 flagsHigh : 8;
    u8 pad_08;
    u8 kind;
    u8 pad_0a[4];
    u16 linkId;
    u16 actorId;
    u8 pad_12[4];
    u16 motionId;
    u8 pad_18[0x58];
    s32 remaining;
} StageEventRecord;

typedef struct StageEventPicker {
    u16 entryId;
    u8 pad_02[2];
    u16 spawnArg;
    u8 pad_06[3];
    u8 flagsLow : 6;
    u8 spawned : 1;
    u8 flagHigh : 1;
    s16 firstEvent;
    s16 lastEvent;
    u8 pad_0e[0xe];
    VecFx32 origin;
} StageEventPicker;

typedef struct StageActor {
    u8 pad_000[0x2c0];
    VecFx32 position;
} StageActor;

typedef struct MotionRecord {
    u8 pad_00[0x14];
    fx32 offsetA;
    fx32 offsetB;
} MotionRecord;

typedef struct LinkItem {
    u8 pad_00[8];
    u8 blocked;
} LinkItem;

typedef struct LinkInfo {
    u32 pad_00;
    u32 count;
    u8 pad_08[4];
    LinkItem *items[1];
} LinkInfo;

typedef struct LinkData {
    u8 pad_00[8];
    LinkInfo *info;
} LinkData;

typedef struct StageLink {
    u16 id;
    u8 pad_02[2];
    LinkData *data;
} StageLink;

extern StageState *data_ov001_020a0528;
extern LargeTableEntry *GetLargeTableEntry(u32 index);
extern void PickStageEventSide(StageEventPicker *picker);
extern StageEventRecord *GetStageEventRecord(u16 eventId);
extern void SpawnStageGroup(StageEventRecord *record, int unused1, int unused2, int arg);
extern StageActor *GetStageActor(int id);
extern void ComputeFormationPosition(const VecFx32 *origin, u32 pattern, fx32 spacing, int index, int count, VecFx32 *out);
extern void SnapToStageGround(StageEventRecord *object, VecFx32 *from, fx32 lift, VecFx32 *pos, int mask, VecFx32 *out);
extern void WarpWalkerTo(StageActor *walker, const VecFx32 *position);
extern int func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern StageLink *FindStageLink(u32 id);
extern void SyncStageEntryPosition(u32 id, VecFx32 *outPosition);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int FX_Atan2Idx(fx32 y, fx32 x);
extern void func_ov001_02090f64(StageActor *actor, int degrees);
extern void func_ov001_0209473c(StageEventRecord *record);
extern MotionRecord *GetStageMotionRecord(u32 id);
extern StageState *func_ov001_0209c3e8(void);

static inline s32 GetSessionMode(void)
{
    if (func_ov001_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

static inline u32 GetLinkItemCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->data == NULL) {
        return 0;
    }
    return link->data->info->count;
}

static inline LinkItem *GetLinkItem(StageLink *link, u32 index)
{
    LinkItem *item;
    u32 count;

    if (link == NULL) {
        return NULL;
    }
    if (link->data == NULL) {
        return NULL;
    }
    count = GetLinkItemCount(link);
    item = link->data->info->items[index];
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return item;
}

void SpawnStageEventGroups(StageEventPicker *picker)
{
    EventGroup *group;
    u16 i;
    u32 pattern;
    EventDef *def;
    u16 spawnArg;
    u16 span;
    u16 lastId;
    u16 eventId;
    u16 slot;
    u16 j;
    EventSide *side;
    StageEventRecord *record;
    StageActor *actor;
    LargeTableEntry *entry;
    StageState *state;
    EventGroupTable *table;
    StageLink *link;
    LinkItem *item;
    MotionRecord *motion;
    StageState *handlerState;
    MotionHandler handler;
    VecFx32 pos;
    VecFx32 diff;
    VecFx32 target;

    state = data_ov001_020a0528;
    table = state->eventGroups;
    entry = GetLargeTableEntry(picker->entryId);
    eventId = picker->firstEvent + 1;
    group = table->groups[entry->groupIndex];
    lastId = picker->lastEvent + 1;

    if (entry->formation == 6) {
        PickStageEventSide(picker);
    }
    slot = 0;
    span = picker->lastEvent - picker->firstEvent + 1;
    for (i = 0; i < group->sideCount; i++) {
        side = &group->sides[i];
        def = &data_ov001_020a0528->eventGroups->defs[side->defIndex];
        pattern = (u16)(span <= 1 ? 0 : entry->formation);
        for (j = 0; j < side->count; j++) {
            BOOL ok = TRUE;
            spawnArg = picker->spawnArg != 0 ? picker->spawnArg + j : 0;
            if (eventId > lastId) {
                break;
            }
            record = GetStageEventRecord(eventId);
            if (record == NULL) {
                ok = FALSE;
            }
            if (record->actorId != 0) {
                ok = FALSE;
            }
            if (record->hidden) {
                ok = FALSE;
            }
            if (state->spawnCounts[side->defIndex] >= def->spawnLimit) {
                ok = FALSE;
            }
            if (ok && record->remaining > 0) {
                SpawnStageGroup(record, 0, 0x1000, spawnArg);
                if (record->actorId != 0) {
                    actor = GetStageActor((s16)record->actorId);
                    ComputeFormationPosition(&picker->origin, pattern, entry->spacing, slot, span, &pos);
                    if (record->kind != 4) {
                        SnapToStageGround(record, &picker->origin, entry->spacing, &pos, 0x1000, &pos);
                    }
                    WarpWalkerTo(actor, &pos);
                    if (GetSessionMode() != 7 && record->kind != 4) {
                        link = FindStageLink(record->linkId);
                        if (link != NULL) {
                            item = GetLinkItem(link, 0);
                            if (item != NULL && item->blocked == 0) {
                                SyncStageEntryPosition(1, &target);
                                VEC_Subtract(&target, &actor->position, &diff);
                                if (VEC_Mag(&diff) >= 4) {
                                    VEC_Normalize(&diff, &diff);
                                    func_ov001_02090f64(actor, (int)(((s64)FX_Atan2Idx(diff.x, diff.z) * 0x1680000 + 0x80000) >> 20));
                                }
                            }
                        }
                    }
                    func_ov001_0209473c(record);
                    if (GetSessionMode() == 7) {
                        motion = GetStageMotionRecord(record->motionId);
                        if (motion != NULL) {
                            if (!picker->spawned) {
                                handlerState = func_ov001_0209c3e8();
                                if (handlerState != NULL && (handler = handlerState->motionHandlers[0]) != NULL) {
                                    handler(motion, &picker->origin, &actor->position);
                                }
                            } else {
                                handlerState = func_ov001_0209c3e8();
                                if (handlerState != NULL && (handler = handlerState->motionHandlers[1]) != NULL) {
                                    handler(motion, &picker->origin, &actor->position);
                                }
                            }
                            motion->offsetA = motion->offsetB = j * -0xf000;
                        }
                    }
                }
            }
            eventId++;
            slot++;
        }
    }
    picker->spawned = 1;
}
