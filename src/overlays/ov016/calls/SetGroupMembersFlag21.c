#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc0];
    u32 flags;
} FieldMember;

typedef struct {
    u8 pad_00[0x3e];
    u16 memberCount;
} FieldGroup;

extern FieldMember *func_ov001_02086384(FieldGroup *group, int index);

void SetGroupMembersFlag21(FieldGroup *group, BOOL enable)
{
    int i;
    FieldMember *member;

    for (i = 0; i < group->memberCount; i++) {
        member = func_ov001_02086384(group, i);
        if (enable) {
            member->flags |= 0x200000;
        } else {
            member->flags &= ~0x200000;
        }
    }
}
