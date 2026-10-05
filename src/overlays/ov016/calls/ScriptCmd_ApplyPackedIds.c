#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct {
    u32 kind : 6;
    u32 first : 10;
    u32 second : 10;
} PackedIds;

extern s32 ScriptVm_ConsumeOperandInt(void *vm, ScriptOperand **cursor);
extern unsigned int func_ov001_0208723c(int index);
extern void func_ov016_020a68f8(unsigned int entry, PackedIds *ids);

BOOL ScriptCmd_ApplyPackedIds(void *vm, ScriptOperand *operands)
{
    ScriptOperand *cursor = operands;
    PackedIds ids;
    int index;

    index = ScriptVm_ConsumeOperandInt(vm, &cursor);
    ids.kind = ScriptVm_ConsumeOperandInt(vm, &cursor);
    ids.first = ScriptVm_ConsumeOperandInt(vm, &cursor);
    ids.second = ScriptVm_ConsumeOperandInt(vm, &cursor);
    func_ov016_020a68f8(func_ov001_0208723c(index), &ids);
    return TRUE;
}
