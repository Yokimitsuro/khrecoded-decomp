#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x14];
    int (*handler)(struct FieldObject *object);
    u8 pad_18[0x28];
    VecFx32 position;
    u8 pad_4c[0x4];
    u16 saveBitOffset;
    u8 saveBitCount;
    s8 linkIndex;
    u8 pad_54[0x4];
    u8 isRunning;
    u8 mode;
    u8 param;
} FieldObject;

extern FieldObject *func_ov001_0207f468(void *objectClass, u8 slotIndex);
extern int UpdateProximityGlow(FieldObject *object);

FieldObject *FieldObject_CreateAtPosition(void *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount,
                                 const VecFx32 *position, int mode, int isRunning, int param)
{
    FieldObject *object = func_ov001_0207f468(objectClass, slotIndex);

    object->position = *position;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->linkIndex = -1;
    object->isRunning = isRunning;
    object->mode = mode;
    object->param = param;
    object->handler = UpdateProximityGlow;
    return object;
}
