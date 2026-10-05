#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern int ChainedConditionCheck(u16 actorId);
extern void func_ov001_020880a8(u16 eventId, u16 animationId);
extern void func_ov001_020880b4(u16 eventId, s32 layer, u16 animationId, s32 option, BOOL persistent);

int ScriptCmd_PlayStageEventAnimation(void *context, ScriptOperand *operands)
{
    int actorId;
    int animationId;
    int option;
    int eventId;

    actorId = ScriptVm_ReadOperandInt(context, &operands[0]);
    animationId = ScriptVm_ReadOperandInt(context, &operands[1]);
    option = ScriptVm_ReadOperandInt(context, &operands[2]);
    eventId = ChainedConditionCheck(actorId);
    func_ov001_020880a8(eventId, animationId);
    func_ov001_020880b4(eventId, 0, animationId, option, TRUE);
    return 1;
}
