#include "nitro/types.h"

typedef struct ScriptActor {
    u8 pad_00[0xb4];
    void *target;
} ScriptActor;

typedef struct ScriptElem {
    u8 handleOperand[4];
    u32 actorId;
    u8 valueOperand[0x10];
    s16 state;
    u8 pad_1A[2];
    int mode;
    u8 pad_20[4];
    int value;
    u8 pad_28[4];
    void *target;
} ScriptElem;

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern s32 ScriptCmd_ReturnValue(void *vm, s32 value);
extern ScriptActor *ActorRegistry_GetEntityByIndex(u16 id);
extern void ScriptCmd_SetElemField(void *vm, ScriptElem *elem);
extern u32 ScriptCmd_SetElemFieldIfFlagSet(void *vm, ScriptElem *elem);

void ScriptCmd_BindActorTarget(void *vm, ScriptElem *elem)
{
    int handle = ScriptVm_ReadOperandInt(vm, elem->handleOperand);
    int value = ScriptVm_ReadOperandInt(vm, elem->valueOperand);
    u32 actorId = ScriptCmd_ReturnValue(vm, handle);

    elem->actorId = actorId;
    elem->value = value;
    elem->target = ActorRegistry_GetEntityByIndex(actorId)->target;
    if (elem->state == 0) {
        elem->mode = 2;
        elem->state = 1;
    }
    ScriptCmd_SetElemField(vm, elem);
    ScriptCmd_SetElemFieldIfFlagSet(vm, elem);
}
