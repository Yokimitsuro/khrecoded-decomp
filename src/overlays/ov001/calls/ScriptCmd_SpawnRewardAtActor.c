#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern void ResumeTaskAndClearFlags(void);
extern u8 *ActorSlot_GetByIndex(u16 actorId);
extern void SpawnRewardOrbs(u16 *amounts, void *position, int flags);

int ScriptCmd_SpawnRewardAtActor(void *vm, u8 *operands) {
    int category = ScriptVm_ReadOperandInt(vm, operands);
    int amount = ScriptVm_ReadOperandInt(vm, operands + 8);
    int actorId = ScriptVm_ReadOperandInt(vm, operands + 0x10);

    ResumeTaskAndClearFlags();
    {
        u16 amounts[6] = {0};
        u8 *actor = ActorSlot_GetByIndex(actorId);
        amounts[category] = amount;
        SpawnRewardOrbs(amounts, actor + 0xb8, 0);
    }
    return 0;
}
