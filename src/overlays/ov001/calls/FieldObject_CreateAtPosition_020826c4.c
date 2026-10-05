#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x40];
    VecFx32 position;
    u16 unk_4c;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 unk_53;
    u32 unk_54;
    u32 unk_58_0 : 15;
    u32 flag15 : 1;
    u32 typeId : 11;
    s32 stateBits : 5;
    u32 userParam;
    u32 unk_60;
    u32 unk_64;
} FieldObject;

extern FieldObject *FieldObject_Create(void *objectClass, u8 slotIndex);

FieldObject *FieldObject_CreateAtPosition_020826c4(void *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, u32 typeId, u32 userParam)
{
    FieldObject *object = FieldObject_Create(objectClass, slotIndex);

    object->position = *position;
    object->unk_4c = 0;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->unk_53 = 0;
    object->typeId = typeId;
    object->userParam = userParam;
    object->stateBits = -1;
    object->unk_64 = 0;
    object->flag15 = 0;
    return object;
}
