#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    u8 data[8];
} ScriptOperand;

extern fx32 ScriptVm_ReadOperandFx32(void *vm, void *operand);
extern void ForwardSubModePairA(int slot, const VecFx32 *value);

int ScriptOp_SetVector4(void *vm, ScriptOperand *operands)
{
    VecFx32 value;

    value.x = ScriptVm_ReadOperandFx32(vm, &operands[0]);
    value.y = ScriptVm_ReadOperandFx32(vm, &operands[1]);
    value.z = ScriptVm_ReadOperandFx32(vm, &operands[2]);
    ForwardSubModePairA(4, &value);
    return 1;
}
