#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6c];
    u16 flagId;
    u16 entryId;
    u16 useEntryBits : 1;
    u16 drawRest : 15;
    u8 pad_72[2];
    s8 slot;
    s8 index;
    u8 pad_76[0x94 - 0x76];
    u32 entryIndex : 10;
    u32 entryMid : 12;
    u32 entryGroup : 10;
    u8 pad_98[0xbd - 0x98];
    u8 unk_BD_low : 4;
    u8 phase : 4;
} FieldObject;

extern BOOL func_ov032_020bf47c(FieldObject *obj);
extern void func_ov001_020645dc(u32 flag);
extern void ClearSessionPackedBit(u32 flag);
extern void func_ov001_020874f4(u32 *record, u32 field0, u32 field1, u32 field2, u32 field3, u32 field4, u32 field5);
extern void GrantEntryUnlockReward(FieldObject *owner, u32 *request);

void GrantFieldObjectReward(FieldObject *obj)
{
    u32 request[6];
    BOOL useIndex;
    u32 index;

    if (obj->phase >= 5 && obj->flagId != 0xffff) {
        if (func_ov032_020bf47c(obj)) {
            func_ov001_020645dc(obj->flagId);
        } else {
            ClearSessionPackedBit(obj->flagId);
        }
    }
    if (obj->useEntryBits) {
        useIndex = FALSE;
        index = obj->entryIndex;
    } else {
        useIndex = TRUE;
        index = obj->index;
    }
    func_ov001_020874f4(request, useIndex, index - 1, obj->entryGroup - 1, obj->slot - 1, obj->flagId, obj->entryId);
    GrantEntryUnlockReward(obj, request);
}
