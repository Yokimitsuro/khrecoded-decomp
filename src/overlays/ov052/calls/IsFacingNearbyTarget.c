#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
} TargetObject;

typedef struct {
    u8 pad_00[0x18];
    TargetObject *object;
} TargetRef;

extern VecFx32 *func_ov052_020ceb74(int entity);
extern u16 func_ov052_020ceb9c(int entity);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_01ffaff4(const VecFx32 *v, VecFx32 *out);
extern u16 FX_Atan2Idx(int vertical, int horizontal);

BOOL IsFacingNearbyTarget(int entity, TargetRef *target)
{
    BOOL result = FALSE;
    VecFx32 *targetPos;
    VecFx32 *selfPos;
    VecFx32 dir;
    fx32 absZ;
    fx32 absX;
    u16 facing;
    int diff;

    if (*(u8 *)(entity + 0x9b4) != 0) {
        return result;
    }
    targetPos = &target->object->position;
    selfPos = func_ov052_020ceb74(entity);
    VEC_Subtract(targetPos, selfPos, &dir);
    dir.y = 0;
    if (VEC_Mag(&dir) >= 0x1b33) {
        return result;
    }
    VEC_Subtract(targetPos, selfPos, &dir);
    if (dir.y >= 0x1000) {
        return result;
    }
    absZ = dir.z < 0 ? -dir.z : dir.z;
    absX = dir.x < 0 ? -dir.x : dir.x;
    if (absX >= absZ) {
        dir.y = 0;
        dir.z = 0;
    } else {
        dir.y = 0;
        dir.x = 0;
    }
    func_01ffaff4(&dir, &dir);
    facing = func_ov052_020ceb9c(entity);
    diff = (u16)(facing - (u16)(FX_Atan2Idx(dir.x, dir.z) + 0x8000));
    if (diff < 0x1555 || diff > 0xeaab) {
        result = TRUE;
    }
    return result;
}
