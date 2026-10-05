#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    u32 packedArgs;
} ScriptCommand;

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern void *func_ov001_0207f050(int actorId);
extern void func_ov007_020a185c(void *actor, u16 emoteId, u16 duration, u8 flags);

BOOL ScriptCmd_ShowActorEmote(void *vm, ScriptCommand *cmd) {
    int actorId = ScriptVm_ReadOperandInt(vm, cmd);
    int emoteId = ScriptVm_ReadOperandInt(vm, (u8 *)cmd + 8);
    u32 packed = cmd->packedArgs;

    func_ov007_020a185c(func_ov001_0207f050(actorId), emoteId, packed, (u16)(packed >> 16));
    return TRUE;
}
