#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct PathPoint {
    s32 easing : 16;
    s32 hold : 16;
    VecFx32 target;
} PathPoint;

typedef struct PathState {
    fx32 time;
    fx32 duration;
    VecFx32 start;
} PathState;

typedef struct PathObject {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[7];
    u8 flags : 7;
    u8 flagsHigh : 1;
    fx32 overflow;
    s32 kind : 16;
    s32 subKind : 12;
    s32 bit28 : 1;
    s32 hitsLeft : 3;
    u8 pad_54[0x14];
    s32 timer;
} PathObject;

extern PathPoint *GetPool1Entry(PathObject *owner, int index);
extern fx32 EaseProgress(fx32 time, fx32 duration, int easing);
extern void LerpVecFx32Q27InPlace(VecFx32 *current, const VecFx32 *target, s32 t);

BOOL StepLinearPathMotion(PathState *state, PathObject *object, int index)
{
    PathPoint *point = GetPool1Entry(object, index);
    VecFx32 position;
    fx32 progress;

    state->time += object->overflow + FX32_ONE;
    object->overflow = 0;
    if (state->time >= state->duration) {
        object->overflow = state->time - state->duration;
        if (state->duration == 0 && point->hold == 0) {
            if (object->subKind == 2) {
                object->timer = 0;
            } else if (state->time < 0x1e000) {
                object->timer = (s64)(0x1e000 - state->time) * 0x5000 / 0x1e000;
                if (!object->bit28) {
                    object->overflow = 0;
                }
                object->bit28 = 0;
                return FALSE;
            } else {
                object->timer = 0;
                object->bit28 = 1;
                object->overflow = state->time - 0x1e000;
            }
            object->flagsHigh = 0;
        }
        object->position = point->target;
        return TRUE;
    }
    progress = EaseProgress(state->time, state->duration, point->easing);
    position = state->start;
    LerpVecFx32Q27InPlace(&position, &point->target, progress << 15);
    object->position = position;
    return FALSE;
}
