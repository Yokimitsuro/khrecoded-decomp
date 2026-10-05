#include "nitro/fx_types.h"

typedef struct {
    u32 baseIndex : 9;
    u8 pad_04[4];
    u32 bits : 3;
    u32 scattering : 1;
    u16 memberCount;
    u8 pad_0e[0x126];
    VecFx32 anchor;
} GroupEntry;

typedef struct {
    u8 pad_00[4];
    u32 unitTable;
} GroupOwner;

extern const VecFx32 data_0205344c;
extern GroupEntry *func_ov032_020bbc80(void *group);
extern u16 *func_ov032_020bbc98(void *unit);
extern u32 func_ov001_02086384(u32 table, u32 index);
extern BOOL IsFieldUnitPhase6(void *unit);

void ResetGroupMemberFlags(GroupOwner *group)
{
    GroupEntry *entry = func_ov032_020bbc80(group);
    int i;

    for (i = 0; i < (u8)entry->memberCount; i++) {
        void *unit = (void *)func_ov001_02086384(group->unitTable, entry->baseIndex + i);
        if (IsFieldUnitPhase6(unit) == FALSE) {
            *func_ov032_020bbc98(unit) = 0;
        }
    }
    entry->anchor = data_0205344c;
    entry->scattering = 0;
}
