#include "nitro/types.h"

extern void ScriptCmd_TweenActorScale(void *scriptContext, void *obj);
extern void ScriptCmd_SetElemField(void *scriptContext, u32 value);

u32 ScriptCmd_SetElemFieldIfFlagSet(void *scriptContext, u8 *obj)
{
    ScriptCmd_TweenActorScale(scriptContext, obj);
    if (*(s32 *)(obj + 0x24) == 0) {
        return 1;
    }
    ScriptCmd_SetElemField(scriptContext, (u32)obj);
    return 0;
}
