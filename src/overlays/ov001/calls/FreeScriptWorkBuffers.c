#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *block);

typedef struct ScriptWork {
    u8 pad_00[0x70];
    void *buffers[16];
} ScriptWork;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptWork *work;
} ScriptContext;

BOOL FreeScriptWorkBuffers(ScriptContext *context)
{
    int index;

    for (index = 0; index < 16; index++) {
        if (context->work->buffers[index] != NULL) {
            NNSi_FndFreeFromDefaultHeap(context->work->buffers[index]);
            context->work->buffers[index] = NULL;
        }
    }
    return TRUE;
}
