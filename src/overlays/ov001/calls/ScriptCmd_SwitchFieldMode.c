#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern BOOL func_ov001_02063200(int mode, int entranceId);

int ScriptCmd_SwitchFieldMode(void *context, ScriptOperand *operands)
{
    int mode;
    int entranceId;

    mode = ScriptVm_ReadOperandInt(context, operands);
    entranceId = ScriptVm_ReadOperandInt(context, operands + 1);
    if (func_ov001_02063200(mode, entranceId) != 0) {
        return 1;
    }
    return 0;
}
