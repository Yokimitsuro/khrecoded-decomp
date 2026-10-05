#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void func_ov001_0208bce8(u32 frameCount, u32 angle);

int ScriptCmd_QueueCameraAngleTransition(void *context, ScriptOperand *operands)
{
    int angleDegrees = ScriptVm_ReadOperandInt(context, operands);
    u32 frameCount = ScriptVm_ReadOperandInt(context, operands + 1);

    func_ov001_0208bce8(frameCount, angleDegrees * 0xb6);
    return 1;
}
