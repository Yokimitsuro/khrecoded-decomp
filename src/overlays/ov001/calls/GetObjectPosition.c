#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PositionedObject PositionedObject;

typedef struct PositionedObjectVTable {
    u8 pad_00[0x2c];
    BOOL (*getPosition)(PositionedObject *object, VecFx32 *out);
} PositionedObjectVTable;

struct PositionedObject {
    u32 unk_00;
    PositionedObjectVTable *vtable;
    u8 pad_08[0x30];
    VecFx32 position;
};

extern BOOL func_ov001_020872e0(PositionedObject *object, VecFx32 *out);

BOOL GetObjectPosition(PositionedObject *object, VecFx32 *out)
{
    if (func_ov001_020872e0(object, out)) {
        if (object->vtable->getPosition != NULL) {
            return object->vtable->getPosition(object, out);
        }
        *out = object->position;
        return TRUE;
    }
    return FALSE;
}
