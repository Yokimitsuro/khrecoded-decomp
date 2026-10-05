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
    s32 timer;
    s32 pulse;
    s32 state;
} BurstState;

typedef struct {
    u8 pad_00[0xc];
    fx32 radius;
    u8 pad_10[0xc];
    s32 armTime;
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
    u8 pad_13c[2];
    s16 hitIds[8];
    u8 pad_14e[2];
    BurstState *burst;
} Projectile;

typedef struct {
    u8 pad_000[0x188];
    s16 soundId;
    u8 pad_18a[2];
    s32 pulseTimes[3];
} ProjectileOwner;

extern void ForEachRecordInRadius(void *filter, void *visitor, VecFx32 *center, fx32 radius, void *userData);
extern void IsRecordAliveAndUnflagged_020d6ea0(void);
extern void func_ov056_020d6ed8(void);
extern void RebindModelAnimTracks(Projectile *proj, int blend);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern HitResult FindStrongestHit(ProjectileOwner *owner, Projectile *proj, VecFx32 *pos, VecFx32 *vel);
extern s16 AdvanceOwnerAnimation(Projectile *proj, fx32 step);

BOOL UpdateBurstProjectile(ProjectileOwner *owner, Projectile *proj, fx32 step)
{
    BurstState *burst;
    ProjectileDef *def;
    HitResult hit;
    VecFx32 pos;
    VecFx32 vel;
    int count;
    int i;

    def = proj->def;
    burst = proj->burst;
    proj->timer += step;
    switch (burst->state) {
    default:
        burst->state = 0;
        break;
    case 0:
    case 2:
        break;
    case 1:
        burst->timer = 0;
        burst->state = 2;
        break;
    case 3:
        burst->timer += step;
        if (burst->timer >= def->armTime) {
            burst->state = 4;
        } else {
            count = 0;
            ForEachRecordInRadius(IsRecordAliveAndUnflagged_020d6ea0, func_ov056_020d6ed8, &proj->position, def->radius, &count);
            if (count > 0) {
                burst->state = 4;
            }
        }
        break;
    case 4:
        RebindModelAnimTracks(proj, 2);
        burst->timer = 0;
        burst->pulse = 0;
        burst->state = 5;
        SpawnSoundSlot(owner->soundId, 1, &proj->position, 0);
    case 5:
        burst->timer += step;
        if (burst->timer < owner->pulseTimes[burst->pulse]) {
            break;
        }
        pos = proj->position;
        vel = proj->velocity;
        proj->phase = 2;
        for (i = 0; i < 8; i++) {
            proj->hitIds[i] = -1;
        }
        hit = FindStrongestHit(owner, proj, &pos, &vel);
        proj->phase = 1;
        if (++burst->pulse < 3) {
            break;
        }
        burst->state = 6;
        break;
    case 6:
        burst->state = 7;
    case 7:
        burst->state = 0;
        break;
    }
    if (proj->phase == 1 && (u16)AdvanceOwnerAnimation(proj, step) != 0) {
        switch (burst->state) {
        case 2:
            RebindModelAnimTracks(proj, 1);
            burst->state = 3;
            break;
        case 5:
        case 6:
        case 7:
            burst->state = 0;
        case 0:
            proj->phase = -1;
            break;
        }
    }
    if (proj->phase == -1) {
        return TRUE;
    }
    return FALSE;
}
