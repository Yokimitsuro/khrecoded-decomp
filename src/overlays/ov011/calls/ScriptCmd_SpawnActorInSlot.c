#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 payload;
} ScriptOperand;

extern s32 ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *FieldObject_Create_020a0fc4(u16 spawnParam);
extern void func_ov001_0207ee2c(s32 slotIndex, void *actor);

BOOL ScriptCmd_SpawnActorInSlot(void *vm, ScriptOperand *operands) {
    s32 slotIndex = ScriptVm_ReadOperandInt(vm, &operands[0]);
    u16 spawnParam = ScriptVm_ReadOperandInt(vm, &operands[1]);
    func_ov001_0207ee2c(slotIndex, FieldObject_Create_020a0fc4(spawnParam));
    return TRUE;
}
