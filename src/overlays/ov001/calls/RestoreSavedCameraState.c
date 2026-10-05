#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorNode {
    u8 pad_00[0xa8];
    VecFx32 position;
} ActorNode;

typedef struct CameraFollowState {
    u8 pad_00[0x38];
    VecFx32 position;
    VecFx32 target;
    VecFx32 savedPosition;
    VecFx32 savedTarget;
    u8 pad_68[0x18];
    s32 angleA;
    s32 angleB;
    s32 savedAngleA;
    s32 savedAngleB;
    s32 timer;
    u8 pad_94[4];
    s32 holdMode;
    u32 anchorActorId;
    u8 pad_a0[0xa0];
    u8 object[4];
} CameraFollowState;

extern CameraFollowState *data_ov001_020a0514;
extern void Obj_SetWord58(void *object, int value);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 id);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void RestoreSavedCameraState(void)
{
    CameraFollowState *state = data_ov001_020a0514;
    VecFx32 offset;

    if (state->holdMode == 1) {
        Obj_SetWord58(state->object, 0);
        return;
    }
    state->holdMode = 0;
    if (state->anchorActorId != (u32)-1) {
        offset = ActorRegistry_GetEntityByIndex(state->anchorActorId)->position;
        VEC_Add(&state->position, &offset, &state->position);
        state->anchorActorId = (u32)-1;
    }
    state->target = state->savedTarget;
    state->position = state->savedPosition;
    state->angleA = state->savedAngleA;
    state->target = state->savedTarget;
    state->angleB = state->savedAngleB;
    state->timer = 0;
}
