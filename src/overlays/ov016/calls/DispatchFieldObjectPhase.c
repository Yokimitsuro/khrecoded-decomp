#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xbd];
    u8 unk_BD_low : 4;
    u8 phase : 4;
    u8 pad_be[2];
    u32 flags;
} FieldObject;

extern void LowerFieldObjectStep(FieldObject *obj);
extern void func_ov016_020a2cc4(FieldObject *obj);
extern void UpdateObjectGroupMembers(FieldObject *obj);
extern void SwayAndDropFieldObject(FieldObject *obj);

void DispatchFieldObjectPhase(FieldObject *obj)
{
    if (obj->flags & 8) {
        return;
    }
    switch (obj->phase) {
    case 2:
    case 4:
        if (!(obj->flags & 0x500)) {
            func_ov016_020a2cc4(obj);
        }
        break;
    case 1:
        LowerFieldObjectStep(obj);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        UpdateObjectGroupMembers(obj);
        break;
    }
    if (obj->flags & 0x100) {
        SwayAndDropFieldObject(obj);
    }
}
