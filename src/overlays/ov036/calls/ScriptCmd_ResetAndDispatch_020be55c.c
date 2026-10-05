#include "nitro/types.h"

extern void SetPanelEnabled(u32 value);
extern void ScriptCmd_SetElemField(void *scriptContext, u32 value);
extern void func_ov036_020be52c(void *scriptContext, u32 value);

void ScriptCmd_ResetAndDispatch_020be55c(void *scriptContext, u32 value)
{
    SetPanelEnabled(0);
    ScriptCmd_SetElemField(scriptContext, value);
    func_ov036_020be52c(scriptContext, value);
}
