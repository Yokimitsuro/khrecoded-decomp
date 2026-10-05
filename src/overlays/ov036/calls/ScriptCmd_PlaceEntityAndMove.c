#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x628];
    s32 isSkipping;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern void MoveSceneModelSlot(int entityId, int startX, int startY, int targetX, int targetY, int duration);

int ScriptCmd_PlaceEntityAndMove(ScriptContext *context, ScriptOperand *operands)
{
    int entityId = ScriptVm_ReadOperandInt(context, &operands[0]);
    int startX = ScriptVm_ReadOperandInt(context, &operands[1]);
    int startY = ScriptVm_ReadOperandInt(context, &operands[2]);
    int targetX = ScriptVm_ReadOperandInt(context, &operands[3]);
    int targetY = ScriptVm_ReadOperandInt(context, &operands[4]);
    int duration = ScriptVm_ReadOperandInt(context, &operands[5]);

    if (context->isSkipping != 0) {
        return 1;
    }
    MoveSceneModelSlot(entityId, startX, startY, targetX, targetY, duration);
    return 1;
}
