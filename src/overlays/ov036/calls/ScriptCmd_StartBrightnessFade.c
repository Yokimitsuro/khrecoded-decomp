#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void StartScreenBrightnessFade_020bd6dc(u32 screen, int level, int duration);

int ScriptCmd_StartBrightnessFade(void *context, ScriptOperand *operands)
{
    int level = ScriptVm_ReadOperandInt(context, &operands[0]);
    int duration = ScriptVm_ReadOperandInt(context, &operands[1]);
    int screen = ScriptVm_ReadOperandInt(context, &operands[2]);

    StartScreenBrightnessFade_020bd6dc(screen, level, duration);
    return 1;
}
