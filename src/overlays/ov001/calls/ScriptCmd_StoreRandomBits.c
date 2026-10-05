#include "nitro/types.h"

typedef struct ScriptCmd {
    u32 opcode;
    u32 bitField;
    u8 operand[1];
} ScriptCmd;

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern u32 func_0202a9e4(u32 range);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

BOOL ScriptCmd_StoreRandomBits(void *vm, ScriptCmd *cmd)
{
    u32 bitField = cmd->bitField;
    u32 value = func_0202a9e4((u16)ScriptVm_ReadOperandInt(vm, cmd->operand));

    WriteSessionPackedBits((u16)bitField, (u8)(u16)(bitField >> 16), value);
    return TRUE;
}
