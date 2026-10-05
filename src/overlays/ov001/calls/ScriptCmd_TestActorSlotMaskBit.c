#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u8 pad_00[4];
    u16 flags;
} ActorNode;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern s16 ActorSlot_GetField1C4ByIndex(u16 actorId);
extern u32 BuildSlotMask(void *slotList, int offset);

int ScriptCmd_TestActorSlotMaskBit(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int bit;
    ActorNode *node;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    bit = ScriptVm_ReadOperandInt(context, operands + 1);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    node = ActorRegistry_GetEntityByIndex(actorId);
    if ((node->flags & 4) == 0) {
        if ((BuildSlotMask(&node->flags, ActorSlot_GetField1C4ByIndex(actorId) << 1) & (1 << bit)) != 0) {
            return 1;
        }
    }
    return 0;
}
