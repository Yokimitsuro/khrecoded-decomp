#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
} VecFx32_2D;

extern fx32 FX_Div(fx32 a, fx32 b);
extern fx32 LengthFx32Xy(fx32 x, fx32 y);

BOOL NormalizeVec2Fx(VecFx32_2D *v, VecFx32_2D *out)
{
    fx32 length = LengthFx32Xy(v->x, v->y);

    if (length != 0) {
        out->x = FX_Div(v->x, length);
        out->y = FX_Div(v->y, length);
        return FALSE;
    }
    return TRUE;
}
