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
extern const char *func_02025dc0(ScriptContext *ctx, void *operand);
extern void *func_0202cc80(const char *path, u32 kind, u32 fromTop);

int ScriptCmd_LoadFileToSlot(ScriptContext *ctx, void *cmd)
{
    int slot = ScriptVm_ReadOperandInt(ctx, cmd);
    const char *path = func_02025dc0(ctx, (u8 *)cmd + 8);

    ctx->fileSlots->loadedFiles[slot] = func_0202cc80(path, 0x11, 0);
    return 1;
}
