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
extern void func_ov001_02063130(int roomId, int entranceId);

int ScriptCmd_RequestRoomChange(ScriptContext *context, ScriptOperand *operands)
{
    int roomId;
    int entranceId;

    roomId = ScriptVm_ReadOperandInt(context, operands);
    entranceId = ScriptVm_ReadOperandInt(context, operands + 1);
    func_ov001_02063130(roomId, entranceId);
    context->waitArmed = 0;
    return 3;
}
