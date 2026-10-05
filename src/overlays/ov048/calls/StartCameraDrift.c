#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct Particle {
    u8 pad00[0x14];
    VecFx32 position;
    VecFx32 origin;
    VecFx32 velocity;
    VecFx32 savedOrigin;
    VecFx32 savedPosition;
} Particle;

typedef struct CameraState {
    u8 pad00[0x18];
    VecFx32 target;
} CameraState;

extern void InitDriftParticleMotion(Particle *particle, const VecFx32 *origin, const VecFx32 *offset, const VecFx32 *velocity);

void StartCameraDrift(CameraState *camera, Particle *particle)
{
    VecFx32 up;
    VecFx32 base;
    base.x = 0;
    base.y = FX32_ONE;
    base.z = 0;
    up = base;
    InitDriftParticleMotion(particle, (VecFx32 *)camera, &camera->target, &up);
    particle->savedOrigin = particle->origin;
    particle->savedPosition = particle->position;
}
