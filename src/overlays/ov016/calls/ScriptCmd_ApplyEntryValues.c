#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct {
    u32 id : 10;
    fx32 values[5];
} EntryParams;

extern s32 ScriptVm_ConsumeOperandInt(void *vm, ScriptOperand **cursor);
extern fx32 ScriptVm_ConsumeOperandFx32(void *vm, ScriptOperand **cursor);
extern unsigned int func_ov001_0208723c(int index);
extern void SetFieldUnitPathPoint(unsigned int entry, EntryParams *params);

BOOL ScriptCmd_ApplyEntryValues(void *vm, ScriptOperand *operands)
{
    EntryParams params;
    ScriptOperand *cursor = operands;
    int index;

    index = ScriptVm_ConsumeOperandInt(vm, &cursor);
    params.id = ScriptVm_ConsumeOperandInt(vm, &cursor);
    params.values[0] = ScriptVm_ConsumeOperandFx32(vm, &cursor);
    params.values[1] = ScriptVm_ConsumeOperandFx32(vm, &cursor);
    params.values[2] = ScriptVm_ConsumeOperandFx32(vm, &cursor);
    params.values[3] = ScriptVm_ConsumeOperandFx32(vm, &cursor);
    params.values[4] = ScriptVm_ConsumeOperandFx32(vm, &cursor);
    SetFieldUnitPathPoint(func_ov001_0208723c(index), &params);
    return TRUE;
}
