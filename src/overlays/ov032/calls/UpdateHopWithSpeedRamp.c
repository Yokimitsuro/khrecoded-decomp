#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[8];
    u32 unk_08_0 : 6;
    u32 stunCount : 10;
    u32 unk_08_16 : 6;
    u32 lockCount : 10;
    u8 pad_0c[0x1d4];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

typedef struct {
    u8 pad_00[8];
    u32 landed : 1;
    u32 rising : 1;
    u32 trackLanding : 1;
    u32 unk_08_bit3 : 1;
    u32 ledgeFound : 1;
    u32 unk_08_rest : 27;
    u8 pad_0c[0x24];
    fx32 speed;
} HopState;

extern BOOL UpdateLedgeClimb(FieldContext *context, int index, HopState *state, VecFx32 *position, VecFx32 *velocity, int collisionArg, VecFx32 *outMove, BOOL *outStopped);
extern BOOL UpdateHopMovement(FieldContext *context, int index, HopState *state, VecFx32 *position, VecFx32 *velocity, int collisionArg, VecFx32 *outMove, BOOL *outStopped);

BOOL UpdateHopWithSpeedRamp(FieldContext *context, int index, HopState *state, VecFx32 *position, VecFx32 *velocity, int collisionArg, VecFx32 *outMove, BOOL *outStopped)
{
    FieldObject *object = &context->objects[index];
    BOOL landed;
    fx32 speed;

    if (state->ledgeFound) {
        landed = UpdateLedgeClimb(context, index, state, position, velocity, collisionArg, outMove, outStopped);
    } else {
        landed = UpdateHopMovement(context, index, state, position, velocity, collisionArg, outMove, outStopped);
    }
    speed = state->speed + 0x52;
    state->speed = speed;
    if (speed > 0x1000) {
        speed = 0x1000;
    }
    state->speed = speed;
    if (object->stunCount != 0) {
        speed -= 0xa4;
        state->speed = speed;
        if (speed < 0) {
            speed = 0;
        }
        state->speed = speed;
    } else if (landed) {
        if (*outStopped && object->lockCount == 0) {
            state->speed = speed * 3 / 10;
        }
        if (state->trackLanding) {
            state->landed = landed;
        }
    }
    return landed;
}
