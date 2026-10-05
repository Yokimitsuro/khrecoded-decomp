#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    void **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

typedef struct ActorEntry {
    u8 pad_000[0x6b0];
    fx32 unk_6B0;
} ActorEntry;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern ActorEntry *GetBoundedEntryField(int index);
extern void ActorObject_InitAnimStateAndSetFlagBit11(void *actor, char *animFileName, int animIndex);

int ScriptCmd_SetActorExtraAnimation(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    switch (operands[1].type) {
    case 1:
    case 0x10:
        GetBoundedEntryField(actorId)->unk_6B0 = ScriptVm_ReadOperandFx32(context, operands + 2);
        break;
    case 2: {
        char *animFileName = ByteCode_ResolveOperand(context, operands + 1);
        int animIndex = ScriptVm_ReadOperandInt(context, operands + 2);
        ActorObject_InitAnimStateAndSetFlagBit11(context->scene->actorObjects[actorId], animFileName, animIndex);
        break;
    }
    }
    return 1;
}
