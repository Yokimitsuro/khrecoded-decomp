#include "nitro/types.h"

typedef struct ObjectDef {
    u8 pad_00[0x5A];
    u8 kind;
} ObjectDef;

typedef struct Object {
    u8 pad_00[4];
    ObjectDef *def;
    u8 pad_08[0x48];
    union {
        s32 value;
        struct {
            u8 pad_00[2];
            u8 level;
        } bytes;
    } param;
} Object;

extern u8 func_ov016_020a6b14(Object *object);

int Object_GetKindValue(Object *object)
{
    switch (object->def->kind) {
    case 9:
        return func_ov016_020a6b14(object);
    case 4:
        return (s16)object->param.value;
    case 5:
        return object->param.bytes.level;
    }
    return 0x15;
}
