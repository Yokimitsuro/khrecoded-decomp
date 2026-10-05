#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x24];
    VecFx32 velocity;
} Body;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void Body_ReflectVelocity(void *context, const VecFx32 *normal, Body *body)
{
    VecFx32 offset;
    VecFx32 scaled;
    VecFx32 reflected;
    fx32 twiceDot = VEC_DotProduct(&body->velocity, normal) * 2;

    scaled = *normal;
    ScaleVecFx32InPlace(&scaled, twiceDot);
    offset = scaled;
    VEC_Subtract(&body->velocity, &offset, &reflected);
    body->velocity = reflected;
}
