#include "nitro/types.h"

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

typedef struct ActorSlot {
    int animation;
    int param;
} ActorSlot;

extern ScriptOperand data_ov001_0209e458;
extern char data_ov001_020a0250[];
extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern u8 *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void *ActorSlot_GetByIndex(u16 actorId);
extern void *QueryLinkTarget(void *owner);
extern void SetFieldOffset5aIfFlag(void *self, int value, int flag);
extern int ComputeHeadingToScriptTarget(ScriptContext *context, ScriptOperand *target, int actorId);
extern void ActorObject_SetSecondarySlot(void *actor, const void *src, int index);
extern void func_ov001_0208a764(void *actorObject, int heading, char *turnAnimation, char *followAnimation);

int ScriptCmd_FaceTargetWithAnims(ScriptContext *context, ScriptOperand *operands)
{
    int actorId = ScriptVm_ReadOperandInt(context, operands);
    int forwardAnim = ScriptVm_ReadOperandInt(context, operands + 1);
    int backwardAnim = ScriptVm_ReadOperandInt(context, operands + 2);
    ScriptOperand target = data_ov001_0209e458;
    u16 current = *(u16 *)(ActorRegistry_GetEntityByIndex(actorId) + 0x80);
    int heading = ComputeHeadingToScriptTarget(context, &target, actorId);

    if (current == heading) {
        void *link = QueryLinkTarget(ActorSlot_GetByIndex(actorId));
        int diff = *(u16 *)((u8 *)link + 0x4c) - current;
        int wrapped = (u16)diff;
        if (wrapped >= 0x8000) {
            forwardAnim = backwardAnim;
        }
        SetFieldOffset5aIfFlag(link, forwardAnim, diff);
    } else {
        ActorSlot slot;
        slot.param = -1;
        slot.animation = forwardAnim;
        ActorObject_SetSecondarySlot(context->scene->actorObjects[actorId], &slot, 0);
        slot.animation = backwardAnim;
        ActorObject_SetSecondarySlot(context->scene->actorObjects[actorId], &slot, 1);
        func_ov001_0208a764(context->scene->actorObjects[actorId], heading, data_ov001_020a0250, 0);
    }
    return 1;
}
