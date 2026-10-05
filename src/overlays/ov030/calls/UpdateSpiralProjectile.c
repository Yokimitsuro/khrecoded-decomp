#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s32 target;
    s32 side;
    s32 strength;
    u8 pad_0c[0xc8];
} HitResult;

typedef struct {
    u8 pad_00[0x18];
    fx32 maxRange;
    s32 lifetime;
} ProjectileDef;

typedef struct {
    u8 pad_00[2];
    s8 phase;
    u8 pad_03;
    s32 timer;
    u8 pad_08[0x10];
    VecFx32 origin;
    VecFx32 velocity;
    u8 pad_30[0xd4 - 0x30];
    VecFx32 position;
    u8 pad_e0[0x138 - 0xe0];
    ProjectileDef *def;
} Projectile;

typedef struct {
    u8 pad_000[0x1c0];
    s32 turnInterval;
} ProjectileOwner;

extern const s16 data_02053580[];
extern void MTX_RotZ33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern HitResult func_ov021_020ab0e8(ProjectileOwner *owner, Projectile *proj, VecFx32 *pos, VecFx32 *vel);
extern s16 AdvanceOwnerAnimation(Projectile *proj, fx32 step);
extern void AdvanceToSecondPhase(Projectile *proj);

BOOL UpdateSpiralProjectile(ProjectileOwner *owner, Projectile *proj, fx32 step)
{
    ProjectileDef *def = proj->def;
    VecFx32 pos;
    VecFx32 vel;
    MtxFx33 rot;
    u16 angle;
    int index;
    BOOL finished;

    proj->timer += step;
    pos = proj->position;
    vel = proj->velocity;
    if (proj->timer % owner->turnInterval == 0) {
        angle = 0x1c70;
        if (vel.y >= 0) {
            angle = 0xe38f;
        }
        if (vel.x < 0) {
            angle = 0xffff - angle;
        }
        index = angle >> 4;
        MTX_RotZ33_(&rot, data_02053580[index], data_02053580[(0x400 - index) & 0xfff]);
        func_01ff9404(&proj->velocity, &rot, &proj->velocity);
    }
    VEC_Add(&pos, &vel, &pos);
    proj->position = pos;
    func_ov021_020ab0e8(owner, proj, &pos, &vel);
    if (proj->phase == 1) {
        finished = FALSE;
        AdvanceOwnerAnimation(proj, step);
        if (def->lifetime >= 0 && proj->timer >= def->lifetime) {
            finished = TRUE;
        }
        if (def->maxRange >= 0 && VEC_Distance(&proj->origin, &pos) > def->maxRange) {
            finished = TRUE;
        }
        if (finished) {
            AdvanceToSecondPhase(proj);
        }
    }
    if (proj->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
