#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Particle {
    u8 pad00[0x14];
    VecFx32 position;
    VecFx32 origin;
} Particle;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);

void GetParticleDriftDirection(Particle *particle, VecFx32 *direction)
{
    VecFx32 normalized;
    VecFx32 offset;
    VecFx32 input;

    VEC_Subtract(&particle->position, &particle->origin, &offset);
    input = offset;
    VEC_Normalize(&input, &normalized);
    *direction = normalized;
}
