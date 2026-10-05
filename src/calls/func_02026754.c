#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x628];
    s32 flag;
} ScriptObj;

extern int ScriptVm_ReadOperandInt(void *obj, void *cmd);
extern void PlaySoundChecked(u32 param1, u32 param2);

int func_02026754(ScriptObj *obj, void *cmd)
{
    int a = ScriptVm_ReadOperandInt(obj, cmd);
    int b = ScriptVm_ReadOperandInt(obj, (u8 *)cmd + 8);
    if (obj->flag != 0) {
        return 1;
    }
    PlaySoundChecked(a, b);
    return 1;
}
