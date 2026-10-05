#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u32 data_ov044_020d0ec0;

extern VecFx32 *func_ov044_020d0598(void);
extern void InitDriftParticle(void *particle, const VecFx32 *position, int param30, int param2c);

void SpawnPanelDriftParticle(int param30, int param2c)
{
    InitDriftParticle((void *)(data_ov044_020d0ec0 + 0x110), func_ov044_020d0598(), param30, param2c);
}
