#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern fx32 ScriptVm_ReadOperandFx32(void *context, ScriptOperand *operand);
extern void func_ov042_020bd76c(fx32 magnitude, fx32 duration);
extern void PlaySoundChecked(u32 bank, u32 soundId);

int ScriptCmd_StartCameraShake(void *context, ScriptOperand *operands)
{
    fx32 magnitude;
    fx32 duration;

    magnitude = ScriptVm_ReadOperandFx32(context, operands);
    duration = ScriptVm_ReadOperandFx32(context, operands + 1);
    func_ov042_020bd76c(magnitude, duration);
    PlaySoundChecked(0, 0x31);
    return 1;
}
