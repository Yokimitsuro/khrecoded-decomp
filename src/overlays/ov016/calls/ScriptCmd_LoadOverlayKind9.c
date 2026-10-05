#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct {
    u8 high;
    u8 low;
    u16 middle;
    s32 param;
} OverlayLoadArgs;

extern s32 ScriptVm_ConsumeOperandInt(void *vm, ScriptOperand **cursor);
extern int func_ov001_02086eb8(u32 kind, int slot, u32 id, OverlayLoadArgs *args);
extern void func_ov001_02086fb8(int index, int entry);

BOOL ScriptCmd_LoadOverlayKind9(void *vm, ScriptOperand *operands)
{
    ScriptOperand *cursor = operands;
    OverlayLoadArgs args;
    int slot;
    u32 id;
    s32 packed;

    slot = ScriptVm_ConsumeOperandInt(vm, &cursor);
    id = ScriptVm_ConsumeOperandInt(vm, &cursor);
    packed = ScriptVm_ConsumeOperandInt(vm, &cursor);
    args.low = packed;
    args.param = ScriptVm_ConsumeOperandInt(vm, &cursor);
    args.high = packed >> 24;
    args.middle = (u8)(packed >> 8);
    func_ov001_02086fb8(slot, func_ov001_02086eb8(9, slot, id, &args));
    return TRUE;
}
