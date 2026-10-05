#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x94];
    u16 facing;
    u8 pad_96[0xbc - 0x96];
    VecFx32 position;
} EntryInfo;

typedef struct {
    u8 pad_000[2];
    s8 phase;
    u8 pad_003[0xd1];
    VecFx32 position;
    u8 pad_0e0[0x154 - 0xe0];
} UnitEntry;

typedef struct TimedUnit TimedUnit;
typedef BOOL (*EntryHandler)(TimedUnit *unit, UnitEntry *entry, s32 step);

struct TimedUnit {
    u8 pad_000[8];
    UnitEntry *entries;
    u8 pad_00c[9];
    u8 entryCount;
    u8 pad_016[0x12];
    EntryHandler handlers[2];
    u8 pad_030[0xc];
    s8 entryIndex;
    u8 pad_03d[2];
    s8 activeCount;
    u8 pad_040[0x14c];
    s32 lifetime;
    u8 pad_190[4];
    s32 armed;
    s32 timer;
    u32 kind;
    u32 subKind;
    s32 power;
};

extern const VecFx32 data_ov056_020d7fc0;
extern EntryInfo *GetBoundedEntryField(int index);
extern void RotateOffsetAroundY(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern BOOL StepEffectAnimation(TimedUnit *unit, s32 step);
extern void SpawnOffsetProjectile(TimedUnit *unit, u32 kind, u32 subKind, s32 power);

void UpdateTimedUnitEntries(TimedUnit *unit, s32 step)
{
    int i;
    UnitEntry *entry;
    EntryInfo *info;
    u16 angle;
    VecFx32 pos;

    for (i = 0; i < unit->entryCount; i++) {
        entry = &unit->entries[i];
        if (entry->phase != -1) {
            info = GetBoundedEntryField(unit->entryIndex);
            pos = data_ov056_020d7fc0;
            angle = info->facing - 0x8000;
            RotateOffsetAroundY(&pos, &info->position, angle + 0x8000, &pos);
            entry->position = pos;
            if (unit->handlers[entry->phase](unit, entry, step)) {
                unit->activeCount--;
            }
        }
    }
    StepEffectAnimation(unit, step);
    if (unit->armed != 0) {
        unit->timer += step;
        if (unit->timer >= unit->lifetime) {
            SpawnOffsetProjectile(unit, unit->kind, unit->subKind, unit->power);
            unit->armed = 0;
        }
    }
}
