#include "nitro/types.h"

typedef struct {
    u32 unk_00_0 : 18;
    u32 mode : 5;
    u32 nextMode : 5;
    u32 unk_00_28 : 4;
    u8 pad_04[4];
    u32 unk_08_0 : 1;
    u32 modeChanged : 1;
    u32 pending : 1;
    u32 unk_08_3 : 29;
    u8 pad_0c[8];
    s16 modeTimer;
    u8 pad_16[0x1ca];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

extern int RollRowDropItem(FieldContext *context, int index);
extern void ApplyModeToGroupFollowers(FieldContext *context, int index, int mode, int arg3, int arg4);

void QueueFieldObjectModeChange(FieldContext *context, int index, BOOL immediate)
{
    FieldObject *object = &context->objects[index];

    if (immediate) {
        object->nextMode = RollRowDropItem(context, index);
        object->mode = object->nextMode;
        object->modeTimer = 0;
        object->pending = 0;
    } else {
        if (object->mode == 3) {
            object->nextMode = RollRowDropItem(context, index);
        } else {
            object->nextMode = 3;
        }
        ApplyModeToGroupFollowers(context, index, 2, 0, 0);
        object->modeTimer = 0x1e;
    }
    object->modeChanged = 1;
}
