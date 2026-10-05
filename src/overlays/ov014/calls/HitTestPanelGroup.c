#include "nitro/types.h"

typedef struct PanelGroup {
    u8 pad_00[0xc];
    u8 layout[0x38];
    u16 *list;
    u8 pad_44[0x2c];
    s32 recordIndex;
    u8 pad_74[0x14];
} PanelGroup;

typedef struct PanelRecord {
    s32 value;
    u8 pad_04[0x64];
} PanelRecord;

typedef struct PanelGroupSet {
    u8 pad_0000[4];
    PanelGroup groups[0x80];
    u8 pad_4604[0x4678 - 0x4604];
    PanelRecord records[1];
} PanelGroupSet;

extern int func_ov014_0206f740(u16 *list, int value, void *layout, int arg4, int arg5);

int HitTestPanelGroup(PanelGroupSet *set, int index, int arg3, int arg4)
{
    PanelGroup *group;

    if (index < 0) {
        return 0;
    }
    group = &set->groups[index];
    return func_ov014_0206f740(group->list, set->records[group->recordIndex].value, group->layout, arg3, arg4);
}
