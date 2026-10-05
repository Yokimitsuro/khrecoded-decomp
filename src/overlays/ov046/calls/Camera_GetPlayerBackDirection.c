#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const s16 data_02053580[];
extern u16 GetBiasAdjustedField(int playerIndex);

void Camera_GetPlayerBackDirection(VecFx32 *out)
{
    int index = GetBiasAdjustedField(0) >> 4;

    out->y = 0;
    out->x = -data_02053580[index];
    out->z = -data_02053580[(0x400 - index) & 0xfff];
}
