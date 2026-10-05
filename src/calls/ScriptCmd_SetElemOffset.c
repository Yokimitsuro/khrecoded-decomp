#include "nitro/types.h"

typedef struct ScriptElem {
    u8 pad_00[0xc];
    s32 base;
    s32 offset;
    u8 pad_14[0x70 - 0x14];
} ScriptElem;

typedef struct ScriptObj {
    u8 pad_00[4];
    ScriptElem elems[1];
} ScriptObj;

int ScriptCmd_SetElemOffset(ScriptObj *obj, s32 *delta) {
    s32 index = *(s32 *)((u8 *)obj + 0x1c4);
    ScriptElem *elem = &obj->elems[index];
    elem->offset = elem->base + *delta;
    return 2;
}
