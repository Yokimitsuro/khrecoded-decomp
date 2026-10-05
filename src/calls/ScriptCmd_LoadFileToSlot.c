#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x58];
    void *loadedFiles[1];
} ScriptFileSlots;

typedef struct {
    u8 pad_000[0x1c8];
    ScriptFileSlots *fileSlots;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *ctx, void *cmd);
extern const char *ByteCode_ResolveOperand(ScriptContext *ctx, void *operand);
extern void *Msg_OpenContainerAndReadHeader(const char *path, u32 kind, u32 fromTop);

int ScriptCmd_LoadFileToSlot(ScriptContext *ctx, void *cmd)
{
    int slot = ScriptVm_ReadOperandInt(ctx, cmd);
    const char *path = ByteCode_ResolveOperand(ctx, (u8 *)cmd + 8);

    ctx->fileSlots->loadedFiles[slot] = Msg_OpenContainerAndReadHeader(path, 0x11, 0);
    return 1;
}
