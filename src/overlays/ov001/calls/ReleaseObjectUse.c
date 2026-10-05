#include "nitro/types.h"

typedef struct FieldObject FieldObject;

typedef struct FieldObjectDef {
    u8 pad_00[0x10];
    void (*onRelease)(FieldObject *object, int reason);
    u8 pad_14[0x6b];
    u8 useCount;
    u8 activeCount;
} FieldObjectDef;

struct FieldObject {
    u8 pad_00[8];
    FieldObjectDef *def;
    u8 pad_0C[0x42];
    u16 flags;
};

void ReleaseObjectUse(FieldObject *object)
{
    FieldObjectDef *def = object->def;

    def->useCount--;
    if (def->activeCount != 0) {
        def->activeCount--;
    }
    if (def->onRelease != NULL) {
        def->onRelease(object, 0);
    }
    object->flags &= 0xfff9;
}
