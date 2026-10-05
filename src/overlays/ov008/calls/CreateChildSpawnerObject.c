#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObjectClass {
    u8 pad_00[0x84];
    s8 blendIndex;
} FieldObjectClass;

typedef struct ChildSlot {
    void *owner;
    u8 pad_04[0x14];
} ChildSlot;

typedef struct FieldObject {
    u8 pad_00[0x14];
    void (*update)(struct FieldObject *object);
    u8 pad_18[0x23];
    u8 lowBits : 4;
    u8 highBits : 4;
    u8 pad_3c[0x4];
    VecFx32 position;
    u16 angle;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    s8 blendIndex;
    u8 pad_54[0x14];
    ChildSlot children[24];
} FieldObject;

extern FieldObject *FieldObject_Create(FieldObjectClass *objectClass, u8 slotIndex);
extern void UpdateChildSpawnerStage(FieldObject *object);

FieldObject *CreateChildSpawnerObject(FieldObjectClass *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, int angle)
{
    FieldObject *object = FieldObject_Create(objectClass, slotIndex);
    int i;

    object->position = *position;
    object->angle = angle;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->blendIndex = objectClass->blendIndex;
    object->highBits = 0;
    object->update = UpdateChildSpawnerStage;
    for (i = 0; i < 24; i++) {
        object->children[i].owner = object;
    }
    return object;
}
