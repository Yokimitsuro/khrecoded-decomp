#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct FieldObject {
    struct FieldObject *prev;
    struct FieldObject *next;
    void *objectClass;
    u8 *work;
    u8 pad_10[0x30];
    VecFx32 position;
    u16 timer;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 state;
} FieldObject;

extern FieldObject *FieldObject_Create(void *objectClass, int slotIndex);
extern int func_ov009_020a0654(FieldObject *object, BOOL visible);

FieldObject *FieldObject_CreateAtPosition_020a0b9c(void *objectClass, int slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, int hidden)
{
    FieldObject *object = FieldObject_Create(objectClass, slotIndex);

    object->position = *position;
    object->timer = 0;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->state = 0;
    *(fx32 *)(object->work + 0x1c0) = FX32_ONE;
    object->flags |= 0x10;
    object->flags |= 0x20;
    if (hidden) {
        func_ov009_020a0654(object, FALSE);
    } else {
        func_ov009_020a0654(object, TRUE);
    }
    return object;
}
