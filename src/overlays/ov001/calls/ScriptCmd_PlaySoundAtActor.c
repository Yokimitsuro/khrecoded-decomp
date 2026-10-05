#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x628];
    s32 unk_628;
} ScriptContext;

typedef struct ActorNode {
    u8 pad_00[0xa8];
    VecFx32 position;
} ActorNode;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern u32 SpawnSoundSlot(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);

int ScriptCmd_PlaySoundAtActor(ScriptContext *context, ScriptOperand *operands)
{
    int seqArcId;
    int soundId;
    int actorId;
    VecFx32 position;

    seqArcId = ScriptVm_ReadOperandInt(context, &operands[0]);
    soundId = ScriptVm_ReadOperandInt(context, &operands[1]);
    actorId = ScriptVm_ReadOperandInt(context, &operands[2]);
    if (context->unk_628 != 0) {
        return 1;
    }
    position = ActorRegistry_GetEntityByIndex(ScriptCmd_ReturnValue(context, actorId))->position;
    SpawnSoundSlot(seqArcId, soundId, &position, 0);
    return 1;
}
