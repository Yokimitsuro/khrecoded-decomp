#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObjectClass FieldObjectClass;

typedef struct {
    u8 pad_00[0x14];
    void (*update)(void *object);
    u8 pad_18[0x23];
    u8 kindLow : 4;
    u8 kindHigh : 4;
    u8 pad_3C[4];
    VecFx32 offset;
    s16 timer;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 saveState;
    u8 pad_54[0x5b];
    u8 state;
    u8 pad_B0;
    s8 frame;
} EmoteObject;

extern const VecFx32 data_0205344c;

extern EmoteObject *FieldObject_Create(FieldObjectClass *objectClass, u8 slotIndex);
extern void func_ov007_020a1138(void *object);

EmoteObject *CreateEmoteFieldObject(FieldObjectClass *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount) {
    EmoteObject *object = FieldObject_Create(objectClass, slotIndex);

    object->timer = 0;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->saveState = 0;
    object->kindHigh = 0;
    object->offset = data_0205344c;
    object->update = func_ov007_020a1138;
    object->flags |= 0x10;
    object->flags |= 0x4000;
    object->frame = -1;
    object->state = 6;
    return object;
}
