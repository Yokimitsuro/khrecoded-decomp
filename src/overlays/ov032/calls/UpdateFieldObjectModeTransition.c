#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 unk_00_0 : 9;
    u32 ownerIndex : 9;
    u32 mode : 5;
    u32 nextMode : 5;
    u32 unk_00_28 : 4;
    u8 pad_04[4];
    u32 unk_08_0 : 1;
    u32 modeChanged : 1;
    u32 unk_08_2 : 30;
    u16 unk_0c_0 : 11;
    u16 cueSounded : 1;
    u16 unk_0c_12 : 4;
    u8 pad_0e[4];
    u16 unk_12;
    u16 modeTimer;
    u8 pad_16[2];
    s16 fade;
    u8 pad_1a[0x1c6];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
} FieldUnit;

extern FieldUnit *func_ov001_02086384(FieldContext *context, int index);
extern void SpawnSoundSlot(int bank, int soundId, VecFx32 *position, int flags);
extern void ApplyModeToGroupFollowers(FieldContext *context, int index, int mode, BOOL hide, BOOL restore);
extern void BeginRowNibbleChange(FieldContext *context, int index);

void UpdateFieldObjectModeTransition(FieldContext *context, int index)
{
    FieldObject *object = &context->objects[index];

    if (object->modeTimer != 0 && !object->cueSounded) {
        SpawnSoundSlot(0xf8, 8, &func_ov001_02086384(context, object->ownerIndex)->position, 5);
        object->cueSounded = 1;
    }
    if (object->modeTimer == 0) {
        BOOL hide = FALSE;
        BOOL restore = FALSE;
        s16 fade;

        if (object->mode != 1 && object->nextMode == 1) {
            hide = TRUE;
        } else if (object->mode == 1 && object->nextMode != 1) {
            restore = TRUE;
        }
        ApplyModeToGroupFollowers(context, index, object->nextMode, hide, restore);
        if (object->nextMode == 1 && object->fade != 0) {
            object->fade -= 0x19a;
            fade = object->fade;
            if (fade < 0) {
                fade = 0;
            }
            object->fade = fade;
        }
        if (object->nextMode == 3) {
            BeginRowNibbleChange(context, index);
        }
        object->mode = object->nextMode;
        object->modeChanged = 0;
        object->unk_12 = 0;
        object->cueSounded = 0;
    } else {
        object->modeTimer--;
    }
}
