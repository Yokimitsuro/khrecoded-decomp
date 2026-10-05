#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 unk_00_0 : 9;
    u32 ownerIndex : 9;
    u32 unk_00_18 : 14;
    u32 unk_04_0 : 8;
    u32 cooldown : 8;
    u32 unk_04_16 : 16;
    u32 unk_08_0 : 6;
    u32 stunCount : 10;
    u32 unk_08_16 : 6;
    u32 lockCount : 10;
    u8 pad_0c[0x1d4];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

typedef struct {
    u8 pad_00[0x30];
    fx32 speed;
} HopState;

extern void *func_ov001_02086384(FieldContext *context, int index);
extern HopState *func_ov032_020bbc98(void *object);
extern void func_ov032_020bbc5c(FieldObject *object, HopState *state);
extern void func_ov032_020bc60c(FieldContext *context, int index);
extern void func_ov032_020bbfa4(FieldContext *context, int index);
extern void func_ov032_020bd460(FieldContext *context, int index);

void TickFieldObjectCounters(FieldContext *context, int index)
{
    FieldObject *object = &context->objects[index];

    if (object->cooldown != 0) {
        object->cooldown--;
    }
    if (object->stunCount != 0) {
        HopState *state = func_ov032_020bbc98(func_ov001_02086384(context, object->ownerIndex));
        object->stunCount--;
        if (object->stunCount == 0 && state->speed == 0) {
            func_ov032_020bbc5c(object, state);
        }
    }
    if (object->lockCount != 0) {
        object->lockCount--;
    }
    func_ov032_020bc60c(context, index);
    func_ov032_020bbfa4(context, index);
    func_ov032_020bd460(context, index);
}
