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
    u8 pad_00[0x1c];
    s32 lifetime;
    u8 pad_20[0x38];
    s16 soundId;
} ProjectileDef;

typedef struct {
    u8 pad_00[2];
    s8 phase;
    u8 pad_03;
    s32 timer;
    u8 pad_08[0x1c];
    VecFx32 velocity;
    u8 pad_30[0xd4 - 0x30];
    VecFx32 position;
    u8 pad_e0[0x138 - 0xe0];
    ProjectileDef *def;
} Projectile;

typedef struct {
    u8 pad_000[0x18c];
    fx32 gravity;
} ProjectileOwner;

extern const VecFx32 data_ov056_020d7fa8;
extern int FX_Mul(int left, int right);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void func_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern HitResult func_ov021_020ab0e8(ProjectileOwner *owner, Projectile *proj, VecFx32 *pos, VecFx32 *vel);
extern s16 func_ov021_020ab43c(Projectile *proj, fx32 step);
extern void func_ov021_020ab610(Projectile *proj);

BOOL UpdateFallingProjectile(ProjectileOwner *owner, Projectile *proj, fx32 step)
{
    ProjectileDef *def = proj->def;
    VecFx32 pos;
    VecFx32 delta;
    VecFx32 fall;
    HitResult hit;

    pos = proj->position;
    func_01ffafb4(FX_Mul(-owner->gravity, step), &data_ov056_020d7fa8, &fall);
    func_01ffa09c(step, &proj->velocity, &fall, &delta);
    func_01ff9e0c(&proj->velocity, &fall, &proj->velocity);
    hit = func_ov021_020ab0e8(owner, proj, &pos, &delta);
    if (hit.strength != 0) {
        proj->position = hit.position;
        SpawnSoundSlot(def->soundId, 1, &hit.position, 0);
    } else {
        func_01ff9e0c(&pos, &delta, &pos);
        proj->position = pos;
    }
    func_ov021_020ab43c(proj, step);
    proj->timer += step;
    if (proj->timer >= def->lifetime) {
        func_ov021_020ab610(proj);
    }
    if (proj->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
