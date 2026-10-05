#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_Mag(const VecFx32 *v);
extern void DivideVecByLength(VecFx32 *v, fx32 length);
extern void ScaleVecFx32InPlace(VecFx32 *v, fx32 scale);

BOOL ClampVecLength(VecFx32 *vec, fx32 maxLength)
{
    fx32 length = VEC_Mag(vec);

    if (length <= maxLength) {
        return FALSE;
    }
    DivideVecByLength(vec, length);
    ScaleVecFx32InPlace(vec, maxLength);
    return TRUE;
}
