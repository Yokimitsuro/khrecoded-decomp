#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x1e0];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

typedef struct {
    u8 pad_00[8];
    u32 jumpPending : 1;
    u32 rising : 1;
    u32 facingFlip : 1;
    u32 unk_08_bit3 : 1;
    u32 ledgeFound : 1;
    u32 unk_08_rest : 27;
    u8 pad_0c[0xc];
    VecFx32 ledgePosition;
} HopState;

typedef struct {
    u8 pad_00[4];
    int solid;
} CollisionHit;

extern fx32 func_ov032_020bbc50(FieldContext *context, int index);
extern fx32 func_ov032_020bcc00(FieldObject *object, HopState *state);
extern CollisionHit *func_ov032_020bcac4(VecFx32 *position, int mask, int arg, VecFx32 *move, VecFx32 *outMove);
extern fx32 func_ov032_020bc654(VecFx32 *velocity, VecFx32 *move);

BOOL UpdateLedgeClimb(FieldContext *context, int index, HopState *state, VecFx32 *position, VecFx32 *velocity, int collisionArg, VecFx32 *outMove, BOOL *outStopped)
{
    FieldObject *object = &context->objects[index];
    fx32 climbSpeed = func_ov032_020bbc50(context, index);
    VecFx32 move;
    fx32 alignment;

    move.x = 0;
    move.y = (fx32)(((s64)climbSpeed * func_ov032_020bcc00(object, state) + 0x800) >> 12);
    move.z = 0;
    if (func_ov032_020bcac4(position, 7, collisionArg, &move, outMove)) {
        alignment = FX32_ONE - func_ov032_020bc654(outMove, &move);
        if ((outMove->x == 0 && outMove->y == 0 && outMove->z == 0) || ((alignment ^ (alignment >> 31)) - (alignment >> 31)) > 0x80) {
            state->ledgeFound = 0;
        }
    } else if (position->y + outMove->y >= state->ledgePosition.y) {
        state->ledgeFound = 0;
    }
    return FALSE;
}
