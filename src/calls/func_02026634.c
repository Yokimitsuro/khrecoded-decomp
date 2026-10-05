#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x628];
    s32 flag;
} ScriptObj;

extern int ScriptVm_ReadOperandInt(void *obj, void *cmd);
extern s32 func_ov001_02063a38(void);
extern void SetSceneCursor(s32 a, s32 b);
extern void func_0204d808(int new_value);
extern s8 gScriptState;

int func_02026634(ScriptObj *obj, void *cmd)
{
    int a = ScriptVm_ReadOperandInt(obj, cmd);
    if (func_ov001_02063a38() == 8) {
        SetSceneCursor(-1, a);
        if (obj->flag != 0) {
            return 1;
        }
    }
    gScriptState = -1;
    func_0204d808(a);
    return 1;
}
