#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0x10];
    u16 flags;
    u8 pad_56[6];
    fx32 stackHeight;
} FieldObject;

extern FieldObject *FindInactiveOwnerAncestor(FieldObject *object);
extern FieldObject *FindInactiveAncestor(FieldObject *object);

void PropagateStackHeight(FieldObject *object)
{
    FieldObject *base = FindInactiveOwnerAncestor(object);
    FieldObject *child;

    object->flags |= 2;
    if (base->flags & 2) {
        object->stackHeight = base->stackHeight + 0x1800;
    } else {
        object->stackHeight = base->position.y;
    }
    child = FindInactiveAncestor(object);
    if (child != NULL) {
        PropagateStackHeight(child);
    }
}
