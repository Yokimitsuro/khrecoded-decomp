#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x92];
    s16 nextId;
    u8 pad_94[0xbd - 0x94];
    u8 unk_BD_low : 4;
    u8 phase : 4;
    u8 unk_BE_low : 4;
    u8 state : 4;
    u8 pad_bf;
    u32 flags;
    u8 pad_c4[0xec - 0xc4];
    fx32 height;
} FieldObject;

extern FieldObject *func_ov001_02086384(void *manager, int id);

void StackLinkedFieldObjects(void *manager, int id, fx32 height, FieldObject **first)
{
    FieldObject *obj;
    BOOL skip;

    if (id == -1) {
        return;
    }
    obj = func_ov001_02086384(manager, id);
    if (obj->phase != 1) {
        return;
    }
    skip = TRUE;
    if (obj->state <= 3 && ((1 << obj->state) & 0xb)) {
        skip = FALSE;
    }
    if (!skip) {
        obj->flags |= 2;
        obj->height = height;
        height += 0x1800;
        if (*first == NULL) {
            *first = obj;
        }
    }
    StackLinkedFieldObjects(manager, obj->nextId, height, first);
}
