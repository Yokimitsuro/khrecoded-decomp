#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern void SaveSessionCheckpoint(u8 flags);

BOOL ScriptCmd_SaveCheckpoint(void *vm, void *operand)
{
    u8 slot = ScriptVm_ReadOperandInt(vm, operand);

    SaveSessionCheckpoint(slot | 0x80);
    return TRUE;
}
