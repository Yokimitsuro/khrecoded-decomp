#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x14];
    void (*update)(struct FieldObject *object);
    u8 pad_18[0x28];
    VecFx32 position;
    u16 angle;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 unk_53;
    u8 pad_54[0x4];
    int phase;
    int mode;
    fx32 timer;
    fx32 duration;
    u8 pad_68[0x4];
    VecFx32 openOffset;
} FieldObject;

extern FieldObject *FieldObject_Create(void *objectClass, u8 slotIndex);
extern void Gimmick_WaitOpenDelay(FieldObject *object);

FieldObject *CreateDelayedGimmickObject(void *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, const VecFx32 *openOffset, fx32 duration, int mode)
{
    FieldObject *object = FieldObject_Create(objectClass, slotIndex);

    object->position = *position;
    object->angle = 0;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->unk_53 = 0;
    object->flags |= 0x4000;
    object->phase = 0;
    object->update = Gimmick_WaitOpenDelay;
    object->openOffset = *openOffset;
    object->duration = duration;
    object->timer = 0;
    object->mode = mode;
    return object;
}
