#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x4a];
    s8 state;
    u8 flags : 7;
} FieldObject;

BOOL IsFieldIdle(FieldObject *object)
{
    if (object->state == 0 && !(object->flags & 2)) {
        return TRUE;
    }
    return FALSE;
}
