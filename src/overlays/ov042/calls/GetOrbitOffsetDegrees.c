#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 GetCameraOrbitOffset(fx32 radians);

void GetOrbitOffsetDegrees(VecFx32 *out, int degrees) {
    *out = GetCameraOrbitOffset((fx32)((s64)degrees * 0x3244 / 0xb4000));
}
