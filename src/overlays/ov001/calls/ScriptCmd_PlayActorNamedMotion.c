#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(void *context, ScriptOperand *operand);
extern void PlayIndexedActorMotion(int actorIndex, int motionId, int mode, char *motionName);

int ScriptCmd_PlayActorNamedMotion(void *context, ScriptOperand *operands)
{
    int actorIndex;
    char *motionName;
    int motionId;
    int mode;

    actorIndex = ScriptVm_ReadOperandInt(context, operands);
    motionName = ByteCode_ResolveOperand(context, operands + 1);
    motionId = ScriptVm_ReadOperandInt(context, operands + 2);
    mode = 0;
    if (operands[3].type != 0) {
        mode = ScriptVm_ReadOperandInt(context, operands + 3);
    }
    PlayIndexedActorMotion(actorIndex, motionId, mode, motionName);
    return 1;
}
