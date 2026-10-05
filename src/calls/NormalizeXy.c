#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 LengthFx32Xy(fx32 x, fx32 y);
extern fx32 FX_Div(fx32 numer, fx32 denom);

fx32 NormalizeXy(fx32 *xy)
{
    fx32 length = LengthFx32Xy(xy[0], xy[1]);

    xy[0] = FX_Div(xy[0], length);
    xy[1] = FX_Div(xy[1], length);
    return length;
}
