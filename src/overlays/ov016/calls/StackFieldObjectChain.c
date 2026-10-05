#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[4];
    void *manager;
    u8 pad_08[0x30 - 0x08];
    u16 flags;
    u8 pad_32[0x3c - 0x32];
    fx32 posY;
    u8 pad_40[0x92 - 0x40];
    s16 linkId;
    u8 pad_94[0xc0 - 0x94];
    u32 stateFlags;
    u8 pad_c4[0xec - 0xc4];
    fx32 restY;
} FieldObject;

extern void StackLinkedFieldObjects(void *manager, int id, fx32 height, FieldObject **first);

void StackFieldObjectChain(FieldObject *obj)
{
    fx32 height;
    FieldObject *first;

    if (obj->stateFlags & 2) {
        height = obj->restY;
    } else {
        height = obj->posY;
    }
    first = NULL;
    StackLinkedFieldObjects(obj->manager, obj->linkId, height, &first);
    if (first != NULL && (obj->flags & 0x10)) {
        first->flags |= 0x10;
    }
}
