#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s8 team;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x1C];
} HitParams;

typedef struct {
    u8 pad_00[0x3C];
    s8 team;
    u8 pad_3D[0x14B];
    s16 hitSoundId;
    u8 pad_18A[0xA];
    s16 hitEffectId;
} HitOwner;

typedef struct {
    u8 pad_00[0x34];
    HitOwner *owner;
    struct HitTracker *tracker;
    s32 active;
} HitSlot;

typedef struct {
    HitSlot slots[8];
    u8 pad_200[0x1C];
    u32 count;
    u32 paletteIndex;
    u32 colorIndex;
    s32 duration;
} HitSlotTable;

typedef struct HitTracker {
    u8 pad_00[0xD4];
    u8 unk_D4[0x6A];
    s16 hitIds[8];
    u8 pad_14E[2];
    HitSlotTable *table;
} HitTracker;

typedef struct {
    HitParams params;
    HitOwner *owner;
    HitTracker *tracker;
} AreaHitSearch;

typedef struct {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x15];
} HitShape;

typedef struct {
    u8 pad_00[0x24];
    s32 unk_24;
} HitQuery;

extern void ZeroBytes0x28(void *obj);
extern void ComputeScaledStats(HitOwner *owner, HitShape *shape, u8 paletteIndex, u8 colorIndex, s32 duration);
extern void InitPathSegment(HitQuery *query, s32 recordId, s32 unused, s8 team, void *filter, s32 flags);
extern void func_ov021_020ac35c(HitShape *shape, HitQuery *query);
extern void StageRecord_SetCallback(u32 id, u32 callback, u32 userData);
extern void CircleActorAroundUnit(void);
extern s32 func_ov021_020a8cc0(HitParams *params, s32 effectId);
extern void SpawnSoundSlot(s32 soundId, s32 mode, VecFx32 *position, s32 flags);

BOOL TryAreaHitOnRecord(s32 recordId, VecFx32 *position, AreaHitSearch *search)
{
    HitOwner *owner = search->owner;
    HitTracker *tracker = search->tracker;
    HitSlotTable *table = tracker->table;
    int i;
    HitShape shape;
    HitQuery query;
    HitSlot *slot;
    s32 status;

    for (i = 0; i < 8; i++) {
        if (recordId == tracker->hitIds[i]) {
            return FALSE;
        }
    }
    if (table->count < 8) {
        ZeroBytes0x28(&shape);
        ComputeScaledStats(owner, &shape, table->paletteIndex, table->colorIndex, table->duration);
        shape.unk_11 = 0;
        shape.unk_12 = 9;
        InitPathSegment(&query, recordId, -1, owner->team, tracker->unk_D4, 0);
        func_ov021_020ac35c(&shape, &query);
        if (query.unk_24 != (s32)0x80000000) {
            slot = &table->slots[table->count];
            slot->owner = owner;
            slot->tracker = tracker;
            slot->active = 1;
            StageRecord_SetCallback(recordId, (u32)CircleActorAroundUnit, (u32)slot);
            tracker->hitIds[table->count++] = recordId;
            search->params.position = *position;
            status = func_ov021_020a8cc0(&search->params, owner->hitEffectId);
            SpawnSoundSlot(owner->hitSoundId, 1, position, 0);
            return status == -1;
        }
    }
    return FALSE;
}
