#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x628];
    s32 flag;
} ScriptObj;

extern int ScriptVm_ReadOperandInt(void *obj, void *cmd);
extern BOOL IsSoundStreamActive(int handleIndex);
extern void PrepareAndStartStream(int param1, int param2);

int func_020267d8(ScriptObj *obj, void *cmd)
{
    int a = ScriptVm_ReadOperandInt(obj, cmd);
    if (obj->flag != 0) {
        return 1;
    }
    if (IsSoundStreamActive(0) != 0) {
        return 0;
    }
    PrepareAndStartStream(0, a);
    return 1;
}
