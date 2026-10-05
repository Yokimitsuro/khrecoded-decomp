#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x1cc];
    s32 armed;
    s32 valueA;
    s32 valueB;
} ScriptObj;

extern int ScriptVm_ReadOperandInt(void *vm, void *cmd);

int ScriptCmd_ArmPair(ScriptObj *obj, void *cmd)
{
    obj->armed = 1;
    obj->valueA = ScriptVm_ReadOperandInt(obj, cmd);
    obj->valueB = ScriptVm_ReadOperandInt(obj, (u8 *)cmd + 8);
    return 3;
}
