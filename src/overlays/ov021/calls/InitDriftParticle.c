#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct DriftParticle {
    int state;
    VecFx32 position;
    VecFx32 velocity;
    u8 pad1c[0xc];
    int timer;
    int param2c;
    int param30;
    u8 pad34[0xc];
    VecFx32 offset;
    int pad4c;
    u32 phase;
} DriftParticle;

extern const VecFx32 data_0205344c;
extern u32 random_next_scaled(u32 range);
extern void func_ov021_020afafc(DriftParticle *particle);

void InitDriftParticle(DriftParticle *particle, const VecFx32 *position, int param30, int param2c)
{
    VecFx32 zero;

    particle->state = 2;
    particle->position = *position;
    particle->timer = 0;
    particle->param2c = param2c;
    particle->param30 = param30;
    particle->phase = random_next_scaled(0x6488);
    zero = data_0205344c;
    particle->offset = zero;
    func_ov021_020afafc(particle);
    particle->velocity = zero;
}
