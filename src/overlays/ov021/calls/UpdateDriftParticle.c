#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct DriftParticle {
    s32 mode;
    VecFx32 axis;
    VecFx32 position;
    VecFx32 basePosition;
    fx32 elapsed;
    fx32 duration;
    union {
        struct {
            VecFx32 velocity;
            fx32 maxSpeed;
            fx32 pullStrength;
            fx32 turnAngle;
        } drift;
        struct {
            fx32 pad_30;
            VecFx32 offset;
            VecFx32 axis;
        } orbit;
    } u;
    fx32 spinProgress;
    fx32 spinPhase;
} DriftParticle;

extern const VecFx32 data_0205344c;

extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void RotateVectorAroundAxis(VecFx32 *vec, const VecFx32 *axis, fx32 angle);
extern fx32 VEC_Mag(const VecFx32 *vec);
extern u32 random_next_scaled(u32 range);
extern fx32 EaseProgress(fx32 value, fx32 range, int mode);
extern void LerpVecFx32Q27InPlace(VecFx32 *vec, const VecFx32 *axis, int angle);
extern long long _s32_div_f(int numerator, int denominator);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void StepDriftEffect(DriftParticle *particle);

BOOL UpdateDriftParticle(DriftParticle *particle)
{
    fx32 fade;

    fade = 0x1000;
    particle->elapsed += 0x1000;
    if (particle->elapsed >= particle->duration) {
        VecFx32 zero;
        particle->mode = 0;
        particle->elapsed = particle->duration;
        zero = data_0205344c;
        particle->basePosition = zero;
        particle->position = zero;
        return TRUE;
    }

    switch (particle->mode) {
    case 1: {
        VecFx32 pull;
        VecFx32 sum;
        fx32 strength;
        fx32 maxSpeed;
        pull = particle->basePosition;
        strength = -particle->u.drift.pullStrength;
        func_01ffaff4(&pull, &pull);
        ScaleVecFx32InPlace(&pull, strength);
        VEC_Add(&particle->u.drift.velocity, &pull, &sum);
        particle->u.drift.velocity = sum;
        RotateVectorAroundAxis(&particle->u.drift.velocity, &particle->axis, particle->u.drift.turnAngle);
        maxSpeed = particle->u.drift.maxSpeed;
        if (VEC_Mag(&particle->u.drift.velocity) > maxSpeed) {
            func_01ffaff4(&particle->u.drift.velocity, &particle->u.drift.velocity);
            ScaleVecFx32InPlace(&particle->u.drift.velocity, maxSpeed);
        }
        break;
    }
    case 2: {
        fx32 progress;
        particle->spinProgress += 0x810;
        progress = particle->spinProgress;
        if (progress >= 0x1000) {
            particle->spinPhase += random_next_scaled(0x3244) + (0x3244 >> 1);
            particle->spinPhase = (int)(_s32_div_f(particle->spinPhase, 0x3244 << 1) >> 32);
            StepDriftEffect(particle);
        } else {
            VecFx32 rotated;
            fx32 eased = EaseProgress(progress, 0x1000, 1);
            rotated = particle->u.orbit.offset;
            LerpVecFx32Q27InPlace(&rotated, &particle->u.orbit.axis, eased << 15);
            particle->basePosition = rotated;
        }
        break;
    }
    }

    {
        VecFx32 sum;
        VecFx32 scaled;
        fx32 ratio = FX_Div(particle->elapsed, particle->duration);
        if (ratio > 0x4cd) {
            fade = 0x1000 - FX_Div(ratio - 0x4cd, 0xb33);
        }
        VEC_Add(&particle->basePosition, &particle->u.drift.velocity, &sum);
        particle->basePosition = sum;
        scaled = particle->basePosition;
        ScaleVecFx32InPlace(&scaled, fade);
        particle->position = scaled;
    }
    return FALSE;
}
