#include "nitro/fx_types.h"

typedef struct {
    u32 baseIndex : 9;
    u8 pad_04[4];
    u32 bits : 3;
    u32 scattering : 1;
    u16 memberCount;
} GroupEntry;

typedef struct {
    u16 flags;
    u8 pad_02[0x16];
    VecFx32 offset;
} MemberState;

typedef struct {
    u8 pad_00[4];
    u32 unitTable;
} GroupOwner;

extern GroupEntry *func_ov032_020bbc80(void *group);
extern MemberState *func_ov032_020bbc98(void *unit);
extern u32 func_ov001_02086384(u32 table, u32 index);
extern BOOL IsFieldUnitPhase6(void *unit);
extern void PickJitteredPlayerOffset(void *unit, VecFx32 *out);

void ScatterGroupMembers(GroupOwner *group)
{
    GroupEntry *entry = func_ov032_020bbc80(group);
    int i;

    for (i = 0; i < (u8)entry->memberCount; i++) {
        void *unit = (void *)func_ov001_02086384(group->unitTable, entry->baseIndex + i);
        MemberState *state = func_ov032_020bbc98(unit);
        if (IsFieldUnitPhase6(unit) == FALSE) {
            state->flags = 0;
        }
        PickJitteredPlayerOffset(unit, &state->offset);
    }
    entry->scattering = 0;
}
