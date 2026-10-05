#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    int baseValue;
    u8 pad_10[0x18];
    int altValue;
} ObjectDef;

typedef struct {
    ObjectDef *def;
    u8 pad_04[0x18];
    int kind;
} ScriptObject;

int GetObjectKindValue(ScriptObject *object) {
    int value = 0;

    switch (object->kind) {
    case 0:
        value = object->def->baseValue;
        break;
    case 3:
        value = object->def->altValue;
        break;
    case 4:
        value = object->def->altValue;
        break;
    default:
        break;
    }
    return value;
}
