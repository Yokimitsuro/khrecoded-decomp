#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern ScriptOperand *ScriptVm_ResolveOperand(void *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(void *context, ScriptOperand *operand);
extern char *strcpy(char *dst, const char *src);

void Script_ResolveMotionNameAndId(void *context, ScriptOperand *operands, int actorId,
                                            int *outMotionId, char *outMotionName)
{
    ScriptOperand *first;
    ScriptOperand *second;

    ScriptVm_ReadOperandInt(context, &operands[1]);
    ScriptVm_ReadOperandInt(context, &operands[4]);
    first = ScriptVm_ResolveOperand(context, &operands[2]);
    second = ScriptVm_ResolveOperand(context, &operands[3]);
    if (first->type == 2) {
        strcpy(outMotionName, ByteCode_ResolveOperand(context, first));
        *outMotionId = ScriptVm_ReadOperandInt(context, second);
        return;
    }
    if (second->type == 2) {
        strcpy(outMotionName, ByteCode_ResolveOperand(context, second));
        *outMotionId = ScriptVm_ReadOperandInt(context, first);
        return;
    }
    *outMotionId = ScriptVm_ReadOperandInt(context, second);
}
