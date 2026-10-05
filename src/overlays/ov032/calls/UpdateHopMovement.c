#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[4];
    u32 surfaceType : 4;
    u32 unk_04_bits : 28;
    u32 unk_08_low : 22;
    u32 lockCount : 10;
    u8 pad_0c[0x1d4];
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
    s16 turnTimer;
    s16 idleTimer;
    int bounceCount;
    u8 pad_14[4];
    VecFx32 ledgePosition;
    u8 pad_24[0xc];
    int canClimb;
} HopState;

typedef struct {
    u8 pad_00[4];
    int solid;
} CollisionHit;

extern u32 random_next_scaled(u32 upperBound);
extern int ScaleValueByLevelFactor(FieldObject *object, HopState *state);
extern void ScaleVectorXZ(VecFx32 *out, VecFx32 *velocity, int speed);
extern CollisionHit *SweepSphereAgainstWorld(VecFx32 *position, int mask, int arg, VecFx32 *move, VecFx32 *outMove);
extern fx32 CosAngleXZ(VecFx32 *velocity, VecFx32 *move);
extern void func_01ffaff4(VecFx32 *in, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL ProbeGroundBelow(VecFx32 *position, fx32 radius, VecFx32 *out);
extern s32 GetRowIdleLimit(void *context, s32 index);
extern s32 GetRowTurnLimit(void *context, s32 index);
extern int RollRowStepChance(void *context, s32 index);

BOOL UpdateHopMovement(FieldContext *context, int index, HopState *state, VecFx32 *position, VecFx32 *velocity, int collisionArg, VecFx32 *outMove, BOOL *outStopped)
{
    FieldObject *object = &context->objects[index];
    VecFx32 move;
    VecFx32 probe;
    VecFx32 offset;
    VecFx32 direction;
    BOOL landed;
    fx32 alignment;
    CollisionHit *hit;
    s32 idleLimit;
    s32 turnLimit;
    fx32 bottomY;
    fx32 groundY;

    if (state->jumpPending) {
        velocity->y = random_next_scaled(0x596) + 0x2cb;
        state->jumpPending = 0;
        state->rising = 1;
        state->bounceCount = 8;
    } else {
        velocity->y -= 0x8f;
    }
    if (state->rising && velocity->y <= 0) {
        state->rising = 0;
    }
    ScaleVectorXZ(&move, velocity, ScaleValueByLevelFactor(object, state));
    if (move.y < 0 && state->bounceCount > 0) {
        velocity->y = 0;
        move.y = 0;
        state->bounceCount--;
    }
    hit = SweepSphereAgainstWorld(position, 7, collisionArg, &move, &move);
    if (hit != NULL && hit->solid != 0) {
        landed = TRUE;
    } else {
        landed = FALSE;
    }
    if (landed) {
        velocity->y = 0;
    }
    alignment = FX32_ONE - CosAngleXZ(velocity, &move);
    if (state->canClimb != 0 && ((move.x == 0 && move.y == 0 && move.z == 0) || ((alignment ^ (alignment >> 31)) - (alignment >> 31)) > 0x80)) {
        direction = *velocity;
        func_01ffaff4(&direction, &direction);
        ScaleVecFx32InPlace(&direction, 0x1800);
        offset = direction;
        VEC_Add(position, &offset, &probe);
        probe.y += 0x1e000;
        if (object->surfaceType != 3 && landed && ProbeGroundBelow(&probe, 0x1800 >> 1, &probe) && probe.y > 0) {
            state->ledgeFound = 1;
            state->ledgePosition = probe;
            state->idleTimer = 0;
        } else {
            *outStopped = TRUE;
            *outMove = move;
            state->turnTimer = 0;
        }
    } else {
        *outStopped = FALSE;
        *outMove = move;
    }
    if (*outStopped) {
        state->idleTimer = 0;
    }
    idleLimit = GetRowIdleLimit(context, index);
    turnLimit = GetRowTurnLimit(context, index);
    if (object->lockCount != 0) {
        state->idleTimer = 0;
    }
    if (state->idleTimer < idleLimit) {
        state->idleTimer++;
    } else if (state->idleTimer == idleLimit && landed) {
        *outStopped = TRUE;
        state->idleTimer = 0;
    }
    if (state->turnTimer < turnLimit) {
        state->turnTimer++;
    } else if (state->turnTimer == turnLimit && landed) {
        state->facingFlip = RollRowStepChance(context, index);
        state->turnTimer = 0;
    }
    bottomY = outMove->y;
    groundY = position->y;
    bottomY += groundY;
    if (bottomY < 0) {
        velocity->y = 0;
        outMove->y = -groundY;
    }
    return landed;
}
