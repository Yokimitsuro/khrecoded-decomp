#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x9c];
    u32 flags : 31;
    u32 flagsTop : 1;
} ScriptContext;

int ScriptOp_SetContextFlag16(ScriptContext *context) {
    context->flags |= 0x10000;
    return 4;
}
