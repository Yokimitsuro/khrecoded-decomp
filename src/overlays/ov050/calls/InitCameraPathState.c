#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraPathInit {
    VecFx32 position;
    VecFx32 target;
} CameraPathInit;

typedef struct CameraPathState {
    VecFx32 position;
    VecFx32 target;
    u8 pad18[0xc];
    VecFx32 startPosition;
    VecFx32 startTarget;
    VecFx32 currentTarget;
} CameraPathState;

extern void *func_ov050_020c3520(void);
extern u32 func_ov050_020c3530(u32 context, u32 data);

void *InitCameraPathState(CameraPathState *state, u32 mode, const CameraPathInit *init)
{
    func_ov050_020c3520();
    state->position = init->position;
    state->startPosition = state->position;
    state->target = init->target;
    state->startTarget = state->target;
    state->currentTarget = state->startTarget;
    return (void *)func_ov050_020c3530;
}
