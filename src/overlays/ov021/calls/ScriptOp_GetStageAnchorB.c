#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x34];
    VecFx32 vector;
} ScriptContext;

typedef struct {
    u8 pad_00000[0x18e60];
    VecFx32 anchorA;
    u8 pad_18E6C[0xc];
    VecFx32 anchorB;
} StageManager;

extern StageManager *func_ov001_0209c3e8(void);

int ScriptOp_GetStageAnchorB(ScriptContext *context) {
    context->vector = func_ov001_0209c3e8()->anchorB;
    return 0;
}
