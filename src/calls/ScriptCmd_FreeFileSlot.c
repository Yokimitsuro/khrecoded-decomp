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
extern void ZeroHalfThenFree(void *file);

int ScriptCmd_FreeFileSlot(ScriptContext *ctx, void *cmd)
{
    int slot = ScriptVm_ReadOperandInt(ctx, cmd);

    if (ctx->fileSlots->loadedFiles[slot] != NULL) {
        ZeroHalfThenFree(ctx->fileSlots->loadedFiles[slot]);
        ctx->fileSlots->loadedFiles[slot] = NULL;
    }
    return 1;
}
