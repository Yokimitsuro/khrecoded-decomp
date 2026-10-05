#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void ActorChannel_ConfigureAndPlay(u32 channelId, u32 param2, s32 resetMode);

int ScriptCmd_PlayActorChannel(void *context, ScriptOperand *operands)
{
    u32 channelId;
    u32 param2;
    int resetMode;

    channelId = ScriptVm_ReadOperandInt(context, operands);
    param2 = ScriptVm_ReadOperandInt(context, operands + 2);
    resetMode = ScriptVm_ReadOperandInt(context, operands + 1);
    ActorChannel_ConfigureAndPlay(channelId, param2, resetMode != 0);
    return 1;
}
