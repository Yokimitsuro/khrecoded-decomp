#include "nitro/types.h"

extern void MIi_CpuClear32(u32 data, void *dst, u32 size);
extern void ScriptCmd_SetElemField(void *scriptContext, u32 value);
extern int IsFieldPanelShown(void);
extern u32 OpenScriptChoiceBalloon(void *scriptContext, u32 value);

u32 ScriptCmd_ResetAndSetElemField(u8 *scriptContext, u32 value)
{
    u32 result;
    int flag;

    *(u32 *)(*(u8 **)(scriptContext + 0x1c8) + 0x54) = 0xffffffff;
    result = 0;
    MIi_CpuClear32(0, *(u8 **)(scriptContext + 0x1c8) + 200, 0x100);
    ScriptCmd_SetElemField(scriptContext, value);
    flag = IsFieldPanelShown();
    if (flag != 0) {
        result = OpenScriptChoiceBalloon(scriptContext, value);
    }
    return result;
}
