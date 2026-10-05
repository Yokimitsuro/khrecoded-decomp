#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 origin;
    VecFx32 velocity;
    u8 pad_18[4];
    fx32 gravity;
} Trajectory;

extern s64 _ll_mul(s64 a, s64 b);

#define FX_MUL_ROUND(a, b) ((fx32)((_ll_mul((a), (b)) + 0x800) >> 12))

void GetTrajectoryPosition(Trajectory *trajectory, fx32 time, VecFx32 *out)
{
    out->y = (FX_MUL_ROUND(trajectory->gravity, FX_MUL_ROUND(time, time)) >> 1) + (trajectory->origin.y + FX_MUL_ROUND(trajectory->velocity.y, time));
    out->x = trajectory->origin.x + FX_MUL_ROUND(trajectory->velocity.x, time);
    out->z = trajectory->origin.z + FX_MUL_ROUND(trajectory->velocity.z, time);
}
