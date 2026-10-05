#include "nitro/types.h"

extern void SetPanelEnabled(u32 value);
extern void ScriptCmd_SetElemField(void *scriptContext, u32 value);
extern void ScriptCmd_LoadEntityModel(void *scriptContext, u32 value);

void ScriptCmd_ResetAndDispatch_020be55c(void *scriptContext, u32 value)
{
    SetPanelEnabled(0);
    ScriptCmd_SetElemField(scriptContext, value);
    ScriptCmd_LoadEntityModel(scriptContext, value);
}
