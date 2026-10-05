#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x14];
    int (*handler)(void);
    u8 pad_18[0x28];
    VecFx32 position;
    u8 pad_4c[0x4];
    u16 saveBitOffset;
    u8 saveBitCount;
} FieldObject;

extern FieldObject *func_ov001_0207f468(void *objectClass, u8 slotIndex);
extern int func_ov001_02081fa8(void);
extern const VecFx32 data_0205344c;

FieldObject *FieldObject_CreateWithSaveBits(void *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount)
{
    FieldObject *object = func_ov001_0207f468(objectClass, slotIndex);

    object->position = data_0205344c;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->handler = func_ov001_02081fa8;
    return object;
}
