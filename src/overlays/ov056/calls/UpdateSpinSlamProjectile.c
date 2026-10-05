#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 target;
    s32 side;
    s32 strength;
    VecFx32 position;
    u8 pad_18[0xbc];
} HitResult;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
    fx32 w;
} Quaternion;

typedef struct {
    u8 pad_00[0x18];
    s32 hitTimer;
} SpinHitSlot;

typedef struct {
    SpinHitSlot slots[8];
    Quaternion spin;
    fx32 spinX;
    fx32 spinY;
    fx32 radius;
    fx32 radiusSpeed;
    u8 pad_100[4];
    s32 state;
} SpinState;

typedef struct {
    u32 flags;
    u8 pad_04[8];
    s32 power;
    u8 pad_10[0x28];
    s32 hitType;
    u8 pad_3c[4];
    VecFx32 knockback;
    u8 pad_4c[4];
    s32 basePower;
    u8 pad_54[0xc];
} ProjectileDef;

typedef struct {
    u8 pad_00[2];
    s8 phase;
    u8 pad_03;
    s32 timer;
    s32 hitParamA;
    s32 hitParamB;
    u8 pad_10[4];
    s32 hitRadius;
    u8 pad_18[0xc];
    VecFx32 velocity;
    u8 pad_30[0xd4 - 0x30];
    VecFx32 position;
    u8 pad_e0[0x138 - 0xe0];
    ProjectileDef *def;
    u8 pad_13c[2];
    s16 hitIds[8];
    u8 pad_14e[2];
    SpinState *spin;
} Projectile;

typedef struct {
    u8 pad_000[0x38];
    void *hitFilter;
    u8 pad_03c[0x18c - 0x3c];
    fx32 spinRate;
    fx32 spinXRate;
    fx32 spinYRate;
} ProjectileOwner;

extern const VecFx32 data_ov056_020d7f9c;
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void QuatFromAxisAngle(Quaternion *out, const VecFx32 *axis, fx32 angle);
extern HitResult FindStrongestHit(ProjectileOwner *owner, Projectile *proj, VecFx32 *pos, VecFx32 *vel);
extern s16 AdvanceOwnerAnimation(Projectile *proj, fx32 step);
extern void QueueMotionOnStageEvent(void);

BOOL UpdateSpinSlamProjectile(ProjectileOwner *owner, Projectile *proj, fx32 step)
{
    ProjectileDef savedDef;
    HitResult sweepHit;
    HitResult finalHit;
    VecFx32 pos;
    VecFx32 vel;
    SpinState *spin;
    s32 savedParamA;
    s32 savedRadius;
    s32 savedParamB;
    int i;
    VecFx32 *knockback;

    proj->timer += step;
    pos = proj->position;
    vel = proj->velocity;
    spin = proj->spin;
    QuatFromAxisAngle(&spin->spin, &data_ov056_020d7f9c, FX_Mul(owner->spinRate, step));
    spin->spinX = FX_Mul(owner->spinXRate, step);
    spin->spinY = FX_Mul(owner->spinYRate, step);
    switch (spin->state) {
    default:
        spin->state = 0;
        break;
    case 0:
        break;
    case 1:
        spin->radius = FX_Mul(0x1800, 0x1800);
        spin->radiusSpeed = 0;
        spin->state = 2;
    case 2:
        if (proj->timer >= 0x4000) {
            spin->state = 3;
        }
        break;
    case 3:
        savedDef = *proj->def;
        savedParamA = proj->hitParamA;
        savedRadius = proj->hitRadius;
        savedParamB = proj->hitParamB;
        proj->phase = 2;
        proj->def->hitType = 9;
        knockback = &proj->def->knockback;
        knockback->z = 0;
        knockback->y = 0;
        knockback->x = 0;
        proj->def->flags |= 0x800;
        proj->def->basePower = proj->def->power;
        proj->hitParamA = 0;
        proj->hitParamB = 0;
        proj->hitRadius = 0x64000;
        owner->hitFilter = QueueMotionOnStageEvent;
        pos.y -= 0x1000;
        sweepHit = FindStrongestHit(owner, proj, &pos, &vel);
        proj->phase = 1;
        owner->hitFilter = NULL;
        *proj->def = savedDef;
        proj->hitParamA = savedParamA;
        proj->hitRadius = savedRadius;
        proj->hitParamB = savedParamB;
        if (proj->timer >= 0x20000) {
            for (i = 0; i < 8; i++) {
                proj->hitIds[i] = -1;
                spin->slots[i].hitTimer = 0;
            }
            spin->state = 4;
        }
        break;
    case 4:
        proj->phase = 2;
        finalHit = FindStrongestHit(owner, proj, &pos, &vel);
        proj->phase = 1;
        spin->state = 5;
    case 5:
        spin->state = 0;
        break;
    }
    if (proj->phase == 1 && (u16)AdvanceOwnerAnimation(proj, step) != 0) {
        proj->phase = -1;
    }
    if (proj->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
