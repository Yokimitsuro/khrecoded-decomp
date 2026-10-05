#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x13];
    u8 scaleMask : 5;
} ChannelScaler;

extern fx32 FX_Mul(fx32 a, fx32 b);

void ScaleMaskedChannels(ChannelScaler *scaler, VecFx32 *vec, fx32 *single, fx32 *balance, int rawScale)
{
    fx32 scale = (s16)rawScale;
    fx32 value;

    if (scaler->scaleMask & 1) {
        vec->x = FX_Mul(vec->x, scale);
    }
    if (scaler->scaleMask & 2) {
        vec->y = FX_Mul(vec->y, scale);
    }
    if (scaler->scaleMask & 4) {
        vec->z = FX_Mul(vec->z, scale);
    }
    if (scaler->scaleMask & 8) {
        *single = FX_Mul(*single, scale);
    }
    if (scaler->scaleMask & 0x10) {
        value = FX_Mul(*balance + 0x1000, scale) - 0x1000;
        if (value < -0x1000) {
            value = -0x1000;
        }
        if (value > 0x1000) {
            value = 0x1000;
        }
        *balance = value;
    }
}
