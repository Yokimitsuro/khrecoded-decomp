#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x628];
    s32 flag;
} ScriptObj;

extern int ScriptVm_ReadOperandInt(void *obj, void *cmd);
extern s32 func_ov001_02063a38(void);
extern void func_ov036_020bd9a0(s32 a, s32 b);
extern int IsSoundParamStale(void);
extern int func_0204d8cc(int arg0, int arg1);
extern s8 gScriptState;

int func_02026678(ScriptObj *obj, void *cmd)
{
    int a = ScriptVm_ReadOperandInt(obj, cmd);
    int b = ScriptVm_ReadOperandInt(obj, (u8 *)cmd + 8);
    if (func_ov001_02063a38() == 8) {
        func_ov036_020bd9a0(a, b);
        if (obj->flag != 0) {
            return 1;
        }
    }
    if (IsSoundParamStale() != 0) {
        func_0204d8cc((u8)a, b);
        gScriptState = a;
    }
    return 1;
}
