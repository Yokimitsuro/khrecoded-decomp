#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *ctx, void *cmd);
extern s32 ScriptCmd_ReturnValue(void *ctx, s32 value);
extern u32 func_ov001_0207ee3c(int entryIndex);
extern u32 func_ov001_0207ee70(int entryIndex);
extern void SetActorResource(int actorIndex, u32 resourceFileId, u32 dataFileId);

int ScriptCmd_SetActorResourceFromTable(void *ctx, void *cmd)
{
    int actorOperand = ScriptVm_ReadOperandInt(ctx, cmd);
    int entryIndex = ScriptVm_ReadOperandInt(ctx, (u8 *)cmd + 8);
    int actorIndex = ScriptCmd_ReturnValue(ctx, actorOperand);
    u32 resourceFileId = func_ov001_0207ee3c(entryIndex);
    u32 dataFileId = func_ov001_0207ee70(entryIndex);

    SetActorResource(actorIndex, resourceFileId, dataFileId);
    return 1;
}
