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
extern fx32 FX_Div(fx32 numer, fx32 denom);

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((fx64)a * b + 0x800LL) >> 12);
}

void StepSmoothValue(int index)
{
    SmoothValue *values = data_ov093_020c5100->smoothValues;
    SmoothValue *value = &values[index];
    fx32 rate = FX_Div(0x7b, 0x266);
    value->current += FxMul(values[index].target - value->current, rate);
}
