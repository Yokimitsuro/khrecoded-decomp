#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x38];
    u8 slotIndex;
    u8 pad_39[0x1F];
    s32 state : 15;
    s32 stateHigh : 17;
    u32 ownerId;
} FieldObject;

typedef struct FieldObjectList {
    u8 pad_00[0x46];
    u16 count;
} FieldObjectList;

extern VecFx32 *func_ov021_020af5d4(void);
extern fx32 func_ov042_020bd5a4(void);
extern FieldObject *func_ov001_0207f4dc(FieldObjectList *list, int index);
extern void *ActorSlot_GetByIndex(u16 slotIndex);
extern void func_ov001_020827ac(FieldObject *object, VecFx32 *target);

BOOL LaunchMatchingFieldObject(FieldObjectList *list, u32 ownerId, fx32 x)
{
    VecFx32 *base = func_ov021_020af5d4();
    fx32 height = base->y + func_ov042_020bd5a4() + 0x1000;
    int count = list->count;
    int i;
    FieldObject *object;
    VecFx32 target;
    VecFx32 position;

    for (i = 0; i < count; i++) {
        object = func_ov001_0207f4dc(list, i);
        if (object->ownerId == ownerId && object->state == 2 && ActorSlot_GetByIndex(object->slotIndex) != NULL) {
            position.x = x;
            position.y = height;
            position.z = 0;
            target = position;
            func_ov001_020827ac(object, &target);
            return TRUE;
        }
    }
    return FALSE;
}
