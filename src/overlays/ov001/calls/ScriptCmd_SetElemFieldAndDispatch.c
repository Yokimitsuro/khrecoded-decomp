#include "nitro/types.h"

extern void ScriptCmd_SetElemField(void *scriptContext, u32 value);
extern int IsFieldPanelShown(void);
extern int ScriptCmd_ShowPendingDialogText(void *scriptContext, u32 arg);
extern u32 func_ov001_0208d760(void *scriptContext, u32 value);

u32 ScriptCmd_SetElemFieldAndDispatch(u8 *scriptContext, u32 value)
{
    int flag;
    u8 *sub;

    ScriptCmd_SetElemField(scriptContext, value);
    flag = IsFieldPanelShown();
    if (flag == 0) {
        return 0;
    }
    sub = *(u8 **)(scriptContext + 0x1c8);
    if (*(s32 *)(sub + 0x1cc) != 0) {
        flag = ScriptCmd_ShowPendingDialogText(scriptContext, *(u32 *)(sub + 0x50));
        if (flag == 1) {
            return func_ov001_0208d760(scriptContext, value);
        }
        return 0;
    }
    return func_ov001_0208d760(scriptContext, value);
}
