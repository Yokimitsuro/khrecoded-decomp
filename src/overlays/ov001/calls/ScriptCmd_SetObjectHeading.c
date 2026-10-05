#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f060(int groupIndex, int entryIndex);
extern s32 _s32_div_f(s32 numerator, s32 denominator);
extern void SetPanelActorState(void *object, u16 heading);

int ScriptCmd_SetObjectHeading(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands + 1);
    int degrees = ScriptVm_ReadOperandInt(vm, operands + 2);
    void *object = func_ov001_0207f060(groupIndex, entryIndex);

    SetPanelActorState(object, _s32_div_f(degrees << 16, 360));
    return 1;
}
