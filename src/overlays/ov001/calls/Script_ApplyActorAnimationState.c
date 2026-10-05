typedef struct ScriptOperand { short type; unsigned char payload[6]; } ScriptOperand;
extern int ScriptVm_ReadOperandInt(void *scriptContext, ScriptOperand *operand);
extern int ByteCode_ResolveOperand(void *scriptContext, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(void *scriptContext, int actorId);
extern void PlayActorAnimationByName(void *actor, int animationArgument, int animationIndex, int enabled);

int Script_ApplyActorAnimationState(void *scriptContext, ScriptOperand *commandOperands)
{
    int actorId = ScriptVm_ReadOperandInt(scriptContext, commandOperands);
    int animationArgument = ByteCode_ResolveOperand(scriptContext, commandOperands + 1);
    int animationIndex = ScriptVm_ReadOperandInt(scriptContext, commandOperands + 2);
    int enabled = ScriptVm_ReadOperandInt(scriptContext, commandOperands + 3) != 0;
    int resolvedActorId = ScriptCmd_ReturnValue(scriptContext, actorId);
    void *actor = *(void **)(*(int *)(*(int *)((char *)scriptContext + 0x1c8) + 0x4c) + resolvedActorId * 4);
    PlayActorAnimationByName(actor, animationArgument, animationIndex, enabled);
    return 1;
}
