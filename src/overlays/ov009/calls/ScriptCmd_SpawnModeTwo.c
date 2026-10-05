#include "nitro/types.h"

extern int func_ov009_020a0654(void *vm, int mode);

int ScriptCmd_SpawnModeTwo(void *vm)
{
    func_ov009_020a0654(vm, 2);
    return 0;
}
