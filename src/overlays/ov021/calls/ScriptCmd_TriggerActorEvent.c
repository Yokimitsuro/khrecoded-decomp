#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[4];
    u16 stateFlags;
    u16 eventFlags;
} StageActor;

typedef struct {
    u8 pad_00[0x1d0];
    u16 mode;
} StageTarget;

typedef struct {
    StageActor *actor;
    u32 pad_04;
    StageTarget *target;
} StageGlobals;

typedef struct {
    u8 pad_00[0x9c];
    u32 firedEvents : 31;
    u32 locked : 1;
} ScriptContext;

extern StageGlobals data_ov021_020b56c4;
extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern void ClearWalkerStepState(StageTarget *target);

int ScriptCmd_TriggerActorEvent(ScriptContext *context, TaggedValue *operand)
{
    int event = ResolveTaggedValueRef(context, operand)->value;
    StageActor *actor = data_ov021_020b56c4.actor;
    StageTarget *target = data_ov021_020b56c4.target;

    if (target->mode == 1 && actor != NULL) {
        switch (event) {
        case 0xc:
            actor->stateFlags |= 1 << 14;
            break;
        case 0x10:
            actor->stateFlags |= 2 << 14;
            break;
        case 0x11:
            actor->eventFlags = (actor->eventFlags & ~1) | 1;
            break;
        case 9:
            actor->eventFlags |= 2;
            break;
        }
    }
    if (target != NULL && event == 9) {
        ClearWalkerStepState(target);
    }
    context->firedEvents |= 1 << event;
    return 0;
}
