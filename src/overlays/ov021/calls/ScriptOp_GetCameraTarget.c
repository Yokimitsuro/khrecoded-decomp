#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x34];
    VecFx32 vector;
} ScriptContext;

typedef struct {
    u8 pad_000[0x2cc];
    VecFx32 target;
} CameraState;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    CameraState *camera;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56c4;

int ScriptOp_GetCameraTarget(ScriptContext *context) {
    context->vector = data_ov021_020b56c4.camera->target;
    return 0;
}
