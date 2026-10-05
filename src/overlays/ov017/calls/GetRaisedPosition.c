#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0xc];
    s8 state;
    u8 pad_51[3];
    u16 flags;
    u8 pad_56[0xe];
    VecFx32 raisedPosition;
} FieldObject;

VecFx32 *GetRaisedPosition(FieldObject *object)
{
    if (!(object->flags & 8) && object->state == 0) {
        object->raisedPosition = object->position;
        object->raisedPosition.y += 0x600;
        return &object->raisedPosition;
    }
    return NULL;
}
