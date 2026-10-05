#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *ctx, void *cmd);
extern s32 ScriptCmd_ReturnValue(void *ctx, s32 value);
extern u32 ObjectManager_GetFirstEntryParam(int entryIndex);
extern u32 ObjectManager_GetSecondEntryParam(int entryIndex);
extern void SetActorResource(int actorIndex, u32 resourceFileId, u32 dataFileId);

int ScriptCmd_SetActorResourceFromTable(void *ctx, void *cmd)
{
    int actorOperand = ScriptVm_ReadOperandInt(ctx, cmd);
    int entryIndex = ScriptVm_ReadOperandInt(ctx, (u8 *)cmd + 8);
    int actorIndex = ScriptCmd_ReturnValue(ctx, actorOperand);
    u32 resourceFileId = ObjectManager_GetFirstEntryParam(entryIndex);
    u32 dataFileId = ObjectManager_GetSecondEntryParam(entryIndex);

    SetActorResource(actorIndex, resourceFileId, dataFileId);
    return 1;
}
