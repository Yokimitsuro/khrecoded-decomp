#include "nitro/types.h"
#include "nitro/fx_types.h"

void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

BOOL AreVecsWithinRange128(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 delta;
    VecFx32 temp;
    BOOL result;
    BOOL nearXy;

    /* Strict per-axis distance below 0x80 */
    VEC_Subtract(a, b, &temp);
    delta = temp;
    result = FALSE;
    nearXy = FALSE;
    if (delta.x < 0x80 && delta.x > -0x80 && delta.y < 0x80 && delta.y > -0x80)
        nearXy = TRUE;
    if (nearXy && delta.z < 0x80 && delta.z > -0x80)
        result = TRUE;
    return result;
}
