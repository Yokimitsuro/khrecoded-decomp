#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x9c];
    u32 flags : 31;
    u32 flagsTop : 1;
} ScriptContext;

int ScriptOp_SetContextFlag0(ScriptContext *context) {
    context->flags |= 1;
    return 4;
}
