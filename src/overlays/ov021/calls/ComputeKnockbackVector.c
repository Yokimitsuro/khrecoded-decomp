#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    VecFx32 *origin;
    u8 pad_04[0x44];
    VecFx32 direction;
    u8 pad_54[4];
    u16 yaw;
} KnockAttacker;

typedef struct {
    u8 pad_00[0x14];
    VecFx32 velocity;
    int mode;
} KnockOptions;

extern const s16 data_02053580[];
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);

VecFx32 ComputeKnockbackVector(KnockAttacker *attacker, KnockOptions *options, VecFx32 *target) {
    VecFx32 dir;
    VecFx32 vel;
    VecFx32 result;
    MtxFx33 rot;
    u16 angle;
    result.y = options->velocity.y;
    switch (options->mode) {
    case 0:
        if (attacker->direction.x != 0 || attacker->direction.y != 0 || attacker->direction.z != 0) {
            dir = attacker->direction;
        } else {
            int index = attacker->yaw >> 4;
            dir.x = -data_02053580[index];
            dir.z = -data_02053580[(0x400 - index) & 0xfff];
        }
        dir.y = 0;
        func_01ffaff4(&dir, &dir);
        vel = options->velocity;
        vel.y = 0;
        func_01ffafb4(VEC_Mag(&vel), &dir, &dir);
        result.x = dir.x;
        result.z = dir.z;
        break;
    case 1:
        VEC_Subtract(target, attacker->origin, &dir);
        vel = options->velocity;
        vel.y = 0;
        angle = FX_Atan2Idx(dir.x, dir.z);
        MTX_RotY33_(&rot, data_02053580[angle >> 4], data_02053580[(0x400 - (angle >> 4)) & 0xfff]);
        MTX_MultVec33(&vel, &rot, &vel);
        result.x = vel.x;
        result.z = vel.z;
        break;
    }
    return result;
}
