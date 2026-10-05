#include "nitro/types.h"

extern int ScriptVm_ReadOperandFx32(void *vm, void *cmd);
extern s64 _ll_mul(s64 left, s64 right);
extern s64 _ll_sdiv(s64 numerator, s64 denominator);
extern void func_ov043_020bca70(int angle);

BOOL ScriptCmd_SetAngleDegrees(void *vm, void *cmd)
{
    int degrees = ScriptVm_ReadOperandFx32(vm, cmd);

    func_ov043_020bca70(_ll_sdiv(_ll_mul(degrees, 0x3244), 0xb4000));
    return TRUE;
}
