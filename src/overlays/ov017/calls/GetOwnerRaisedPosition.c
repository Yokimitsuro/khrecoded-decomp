#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldOwner {
    u8 pad_00[0x60];
    VecFx32 raisedPosition;
} FieldOwner;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldOwner *owner;
    u8 pad_08[0x30];
    VecFx32 position;
    u8 pad_44[6];
    s8 state;
    u8 flags : 7;
} FieldObject;

VecFx32 *GetOwnerRaisedPosition(FieldObject *object)
{
    FieldOwner *owner = object->owner;

    if (!(object->flags & 2) && object->state == 0) {
        owner->raisedPosition = object->position;
        owner->raisedPosition.y += 0x600;
        return &owner->raisedPosition;
    }
    return NULL;
}
