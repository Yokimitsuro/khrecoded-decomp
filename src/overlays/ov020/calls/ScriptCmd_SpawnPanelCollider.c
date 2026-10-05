#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0208723c(int tableIndex);
extern u8 SpawnPanelCollider(void *owner, u16 kind, int tag, const VecFx32 *position);

int ScriptCmd_SpawnPanelCollider(void *vm, ScriptOperand *operands)
{
    int tableIndex = ScriptVm_ReadOperandInt(vm, operands);
    int kind = ScriptVm_ReadOperandInt(vm, operands + 1);
    int tag = ScriptVm_ReadOperandInt(vm, operands + 2);
    VecFx32 position;

    position.x = ScriptVm_ReadOperandFx32(vm, operands + 3);
    position.y = ScriptVm_ReadOperandFx32(vm, operands + 4);
    position.z = ScriptVm_ReadOperandFx32(vm, operands + 5);
    SpawnPanelCollider(func_ov001_0208723c(tableIndex), kind, tag, &position);
    return 1;
}
