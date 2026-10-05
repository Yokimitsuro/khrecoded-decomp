typedef struct ScriptOperand { short type; unsigned char payload[6]; } ScriptOperand;
typedef struct ActorNode {
    unsigned int flags_000;
    unsigned short flags_004;
    unsigned char reserved_006[0x76];
    unsigned int modelResource;
    unsigned short halfword_080;
} ActorNode;
extern int ScriptVm_ReadOperandInt(void *scriptContext, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(void *scriptContext, int actorId);
extern int _s32_div_f(int fixedValue, int divisorOrScale);
extern ActorNode *ActorRegistry_GetEntityByIndex(unsigned short actorId);
extern void ActorObject_SynchronizeConvertedParameter(void *object, unsigned short value);

int Script_SetActorParameterFromInteger(void *scriptContext, ScriptOperand *commandOperands)
{
    int actorId = ScriptVm_ReadOperandInt(scriptContext, commandOperands);
    int scriptValue = ScriptVm_ReadOperandInt(scriptContext, commandOperands + 1);
    unsigned int resolvedActorId = (unsigned int)ScriptCmd_ReturnValue(scriptContext, actorId);
    unsigned int scaledScriptValue = (unsigned int)scriptValue << 16;
    unsigned short convertedValue = (unsigned short)_s32_div_f((int)scaledScriptValue, 0x168);
    ActorNode *actorNode = ActorRegistry_GetEntityByIndex((unsigned short)resolvedActorId);
    if ((actorNode->flags_000 & 0x20) == 0) {
        actorNode->halfword_080 = convertedValue;
        actorNode->flags_004 |= 0x20;
    }
    void *actorObject = (void *)*(int *)(*(int *)(*(int *)((char *)scriptContext + 0x1c8) + 0x4c) +
                                          resolvedActorId * 4);
    if (actorObject != 0 && (*(int *)((char *)actorObject + 0xd18) != 0 ||
                             (*(unsigned int *)((char *)actorObject + 0xef4) & 0x4000) != 0)) {
        ActorObject_SynchronizeConvertedParameter(actorObject, convertedValue);
    }
    return 1;
}
