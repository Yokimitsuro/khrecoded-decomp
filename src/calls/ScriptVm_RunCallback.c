#include "nitro/types.h"

typedef int (*ScriptCallbackFunc)(void *ctx, int arg);

typedef struct ScriptCallback {
    ScriptCallbackFunc func;
    s32 arg;
} ScriptCallback;

typedef struct ScriptElem {
    u8 pad_00[0x1c];
    ScriptCallback *current;
    ScriptCallback callbacks[10];
} ScriptElem;

typedef struct ScriptObj {
    u8 pad_00[0x1c4];
    s32 currentIndex;
} ScriptObj;

int ScriptVm_RunCallback(ScriptObj *ctx, s32 *pValue)
{
    ScriptElem *elem = (ScriptElem *)((u8 *)ctx + 4 + ctx->currentIndex * 0x70);
    s32 idx = *pValue - 1;
    s32 result = 1;

    if (elem->callbacks[idx].func != 0) {
        result = elem->callbacks[idx].func(ctx, elem->callbacks[idx].arg);
        if (result == 0) {
            elem->current = &elem->callbacks[idx];
        } else {
            elem->callbacks[idx].func = 0;
            elem->callbacks[idx].arg = 0;
        }
    }

    return result;
}
