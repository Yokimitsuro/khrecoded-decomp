#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4c];
    u8 **actorWork;
} ScriptWorld;

typedef struct {
    u8 pad_000[0x1c8];
    ScriptWorld *world;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *ctx, void *cmd);
extern char *func_02025dc0(ScriptContext *ctx, void *operand);
extern u32 ParseSlotQuantityId(ScriptWorld *world, char *name);
extern s32 ScriptCmd_ReturnValue(ScriptContext *ctx, s32 value);
extern u32 func_02036824(u16 actorIndex);
extern void AllocateSlotIfNull(ScriptContext *ctx, int index);
extern void func_02036864(void *work, u16 actorIndex);
extern void SetActorResource(int actorIndex, u32 resourceFileId, u32 dataFileId);

int ScriptCmd_SetActorResourceFromPaths(ScriptContext *ctx, u8 *cmd)
{
    int actorOperand = ScriptVm_ReadOperandInt(ctx, cmd);
    u32 resourceFileId = ParseSlotQuantityId(ctx->world, func_02025dc0(ctx, cmd + 8));
    u32 dataFileId = ParseSlotQuantityId(ctx->world, func_02025dc0(ctx, cmd + 0x10));
    int actorIndex = ScriptCmd_ReturnValue(ctx, actorOperand);

    if (func_02036824(actorIndex) == 0) {
        AllocateSlotIfNull(ctx, actorIndex);
        func_02036864(ctx->world->actorWork[actorIndex] + 0xd24, actorIndex);
    }
    SetActorResource(actorIndex, resourceFileId, dataFileId);
    return 1;
}
