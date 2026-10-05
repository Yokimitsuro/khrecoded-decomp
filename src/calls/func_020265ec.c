#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x628];
    s32 flag;
} ScriptObj;

extern int ScriptVm_ReadOperandInt(void *obj, void *cmd);
extern s32 func_ov001_02063a38(void);
extern void SetSceneCursor(s32 a, s32 b);
extern int IsSoundParamStale(void);
extern int SetSelectionIfChanged(int selection);
extern s8 gScriptState;

int func_020265ec(ScriptObj *obj, void *cmd)
{
    int a = ScriptVm_ReadOperandInt(obj, cmd);
    if (func_ov001_02063a38() == 8) {
        SetSceneCursor(a, 0);
        if (obj->flag != 0) {
            return 1;
        }
    }
    if (IsSoundParamStale() != 0) {
        gScriptState = a;
        SetSelectionIfChanged((u8)a);
    }
    return 1;
}
