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
extern char *ByteCode_ResolveOperand(ScriptContext *ctx, void *operand);
extern u32 ParseSlotQuantityId(ScriptWorld *world, char *name);
extern s32 ScriptCmd_ReturnValue(ScriptContext *ctx, s32 value);
extern u32 ActorSlot_GetByIndex(u16 actorIndex);
extern void AllocateSlotIfNull(ScriptContext *ctx, int index);
extern void ActorRegistry_RegisterSlot(void *work, u16 actorIndex);
extern void SetActorResource(int actorIndex, u32 resourceFileId, u32 dataFileId);

int ScriptCmd_SetActorResourceFromPaths(ScriptContext *ctx, u8 *cmd)
{
    int actorOperand = ScriptVm_ReadOperandInt(ctx, cmd);
    u32 resourceFileId = ParseSlotQuantityId(ctx->world, ByteCode_ResolveOperand(ctx, cmd + 8));
    u32 dataFileId = ParseSlotQuantityId(ctx->world, ByteCode_ResolveOperand(ctx, cmd + 0x10));
    int actorIndex = ScriptCmd_ReturnValue(ctx, actorOperand);

    if (ActorSlot_GetByIndex(actorIndex) == 0) {
        AllocateSlotIfNull(ctx, actorIndex);
        ActorRegistry_RegisterSlot(ctx->world->actorWork[actorIndex] + 0xd24, actorIndex);
    }
    SetActorResource(actorIndex, resourceFileId, dataFileId);
    return 1;
}
