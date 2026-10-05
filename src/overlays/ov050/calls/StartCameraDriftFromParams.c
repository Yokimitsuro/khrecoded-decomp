#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Particle {
    u8 pad00[0x14];
    VecFx32 position;
    VecFx32 origin;
    VecFx32 velocity;
    VecFx32 savedOrigin;
    VecFx32 savedPosition;
} Particle;

typedef struct DriftParams {
    VecFx32 origin;
    VecFx32 offset;
    VecFx32 velocity;
} DriftParams;

extern void InitDriftParticleMotion(Particle *particle, const VecFx32 *origin, const VecFx32 *offset, const VecFx32 *velocity);

void StartCameraDriftFromParams(DriftParams *params, Particle *particle)
{
    InitDriftParticleMotion(particle, &params->origin, &params->offset, &params->velocity);
    particle->savedOrigin = particle->origin;
    particle->savedPosition = particle->position;
}
