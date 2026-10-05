#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraState {
    u8 pad00[0x18];
    VecFx32 target;
} CameraState;

typedef struct CameraParams {
    u8 pad00[0xc];
    VecFx32 target;
} CameraParams;

extern void *func_ov048_020c3520(void);
extern u32 func_ov048_020c3530(u32 context, u32 data);

void *InitCameraTarget(CameraState *camera, u32 mode, CameraParams *params)
{
    func_ov048_020c3520();
    camera->target = params->target;
    return (void *)func_ov048_020c3530;
}
