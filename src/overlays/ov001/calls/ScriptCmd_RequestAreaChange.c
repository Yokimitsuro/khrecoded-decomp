#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x1cc];
    s32 waitArmed;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern void ConfigureFieldTracks(int areaId, int roomId, int entranceId, int transitionFlags);

int ScriptCmd_RequestAreaChange(ScriptContext *context, ScriptOperand *operands)
{
    int areaId;
    int entranceId;

    areaId = ScriptVm_ReadOperandInt(context, operands);
    entranceId = ScriptVm_ReadOperandInt(context, operands + 1);
    ConfigureFieldTracks(areaId, 0, entranceId, -1);
    context->waitArmed = 0;
    return 3;
}
