#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x64];
    VecFx32 velocity;
} Obj;

extern const VecFx32 data_0205344c;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int FX_Mul(int left, int right);
extern void VEC_MultAdd(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern fx32 VEC_Mag(const VecFx32 *v);

void BounceVelocityOffNormal(void *unused, const VecFx32 *normal, Obj *obj)
{
    fx32 dot;

    if (obj->velocity.x != 0 || obj->velocity.y != 0 || obj->velocity.z != 0) {
        dot = VEC_DotProduct(&obj->velocity, normal);
        VEC_MultAdd(-(dot + FX_Mul(dot, 0x4cd)), normal, &obj->velocity, &obj->velocity);
        if (VEC_Mag(&obj->velocity) <= 0x80) {
            obj->velocity = data_0205344c;
        }
    }
}
