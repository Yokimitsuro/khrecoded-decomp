#include "nitro/types.h"
#include "nitro/fx_types.h"

#define INT_TO_FX32(n) ((fx32)((float)(n) > 0 ? 0.5f + 4096.0f * (float)(n) : 4096.0f * (float)(n) - 0.5f))

typedef struct {
    fx32 target;
    fx32 current;
} SmoothValue;

typedef struct {
    u8 pad_0000[0xd1e4];
    SmoothValue smoothValues[2];
} SceneWork;

extern SceneWork *data_ov093_020c5100;

void SetSmoothValueImmediate(int index, int value)
{
    SmoothValue *smooth = &data_ov093_020c5100->smoothValues[index];
    smooth->target = INT_TO_FX32(value);
    smooth->current = INT_TO_FX32(value);
}
