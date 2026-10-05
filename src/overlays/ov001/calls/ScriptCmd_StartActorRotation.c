#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorObject ActorObject;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    ActorObject **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern void *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void StartActorMotionTo(ActorObject *actor, const char *name, const VecFx32 *target, int duration, int extra);

int ScriptCmd_StartActorRotation(ScriptContext *context, ScriptOperand *operands)
{
    int slot = ScriptVm_ReadOperandInt(context, &operands[0]);
    int degX = ScriptVm_ReadOperandInt(context, &operands[2]);
    int degY = ScriptVm_ReadOperandInt(context, &operands[3]);
    int degZ = ScriptVm_ReadOperandInt(context, &operands[4]);
    int duration = ScriptVm_ReadOperandInt(context, &operands[5]);
    int extra = ScriptVm_ReadOperandInt(context, &operands[6]);
    const char *name = ByteCode_ResolveOperand(context, &operands[1]);
    int index = ScriptCmd_ReturnValue(context, slot);
    VecFx32 angles;

    angles.x = degX * 0xb6;
    angles.y = degY * 0xb6;
    angles.z = degZ * 0xb6;
    StartActorMotionTo(context->scene->actorObjects[index], name, &angles, duration, extra);
    return 1;
}
