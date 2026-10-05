#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorTable {
    u8 pad_00[0x4C];
    void **actors;
} ActorTable;

typedef struct ScriptContext {
    u8 pad_000[0x1C8];
    ActorTable *actorTable;
    u8 pad_1CC[0x45C];
    s32 skip;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern int ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern void InitActorDialogTimer(void *actor, int value);
extern void StartActorAnimState(void *actor, int state, int value);

BOOL ScriptCmd_ActorTimerOrAnim(ScriptContext *context, ScriptOperand *operands)
{
    int handle = ScriptVm_ReadOperandInt(context, operands);
    int index;
    int state;

    if (context->skip != 0) {
        return TRUE;
    }
    index = ScriptCmd_ReturnValue(context, handle);
    switch (operands[1].type) {
    case 1:
        InitActorDialogTimer(context->actorTable->actors[index], ScriptVm_ReadOperandInt(context, &operands[1]));
        break;
    case 2:
        state = ByteCode_ResolveOperand(context, &operands[1]);
        StartActorAnimState(context->actorTable->actors[index], state, ScriptVm_ReadOperandInt(context, &operands[2]));
        break;
    }
    return TRUE;
}
