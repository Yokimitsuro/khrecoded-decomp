#include "nitro/types.h"

typedef struct {
    s8 inUse;
    u8 pad_01[3];
    u16 value;
    u8 pad_06[0x132];
} EntrySlot;

typedef struct {
    EntrySlot *slots;
    s32 slotCount;
} EntryGroup;

extern BOOL data_ov021_020b5628;
extern EntryGroup *func_ov021_020a8830(int groupId);

u16 GetGroupSlotValue(int groupId, int index)
{
    EntryGroup *group;
    u16 value = 0;

    if (data_ov021_020b5628 == FALSE) {
        return value;
    }
    group = func_ov021_020a8830(groupId);
    if (group != NULL) {
        value = group->slots[index].value;
    }
    return value;
}
