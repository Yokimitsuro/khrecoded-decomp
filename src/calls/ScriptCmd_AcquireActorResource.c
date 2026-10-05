#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *sharedRecord;
    u8 pad_0c[0x40];
    u8 **actorWork;
} ScriptWorld;

typedef struct {
    u8 pad_000[0x1c8];
    ScriptWorld *world;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *ctx, void *cmd);
extern char *func_02025dc0(ScriptContext *ctx, void *operand);
extern s32 ScriptCmd_ReturnValue(ScriptContext *ctx, s32 value);
extern u32 func_02036824(u16 actorIndex);
extern void AllocateSlotIfNull(ScriptContext *ctx, int index);
extern void func_02036864(void *work, u16 actorIndex);
extern u32 ParseSlotQuantityId(ScriptWorld *world, char *name);
extern int AcquireSharedRecord(u32 fileId, void **out, int kind);
extern void func_020358ac(u16 actorIndex, void *record, int a2, int kind);
extern void ScriptCmd_SetElemField(ScriptContext *ctx, s32 value);

int ScriptCmd_AcquireActorResource(ScriptContext *ctx, u8 *cmd)
{
    int actorOperand = ScriptVm_ReadOperandInt(ctx, cmd);
    char *path = func_02025dc0(ctx, cmd + 8);
    s32 actorIndex = ScriptCmd_ReturnValue(ctx, actorOperand);
    ScriptWorld *world;

    if (func_02036824(actorIndex) == 0) {
        AllocateSlotIfNull(ctx, actorIndex);
        func_02036864(ctx->world->actorWork[actorIndex] + 0xd24, actorIndex);
    }
    world = ctx->world;
    if (AcquireSharedRecord(ParseSlotQuantityId(world, path), &world->sharedRecord, 0xd) != 0) {
        func_020358ac(actorIndex, ctx->world->sharedRecord, 0, 0xd);
        if (actorIndex == 0) {
            ScriptCmd_SetElemField(ctx, -99);
        } else {
            ScriptCmd_SetElemField(ctx, -actorIndex);
        }
    } else {
        ScriptCmd_SetElemField(ctx, actorIndex);
    }
    return 0;
}
