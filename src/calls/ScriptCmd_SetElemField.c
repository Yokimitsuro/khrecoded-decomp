#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x1c4];
    s32 currentIndex;
} ScriptObj;

void ScriptCmd_SetElemField(ScriptObj *obj, u32 value) {
    *(u32 *)((u8 *)obj + obj->currentIndex * 0x70 + 0x20) = value;
}
