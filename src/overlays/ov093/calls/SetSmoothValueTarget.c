#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 target;
    fx32 current;
} SmoothValue;

typedef struct {
    u8 pad_0000[0xd1e4];
    SmoothValue smoothValues[2];
} SceneWork;

extern SceneWork *data_ov093_020c5100;

void SetSmoothValueTarget(int index, int value)
{
    SmoothValue *values = data_ov093_020c5100->smoothValues;
    values[index].target = (fx32)((float)value > 0 ? 0.5f + 4096.0f * (float)value : 4096.0f * (float)value - 0.5f);
}
