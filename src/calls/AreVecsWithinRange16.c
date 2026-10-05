#include "nitro/types.h"
#include "nitro/fx_types.h"

void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 delta;
    VecFx32 temp;
    BOOL result;
    BOOL nearXy;

    /* Strict per-axis distance below 0x10 */
    func_01ff9e3c(a, b, &temp);
    delta = temp;
    result = FALSE;
    nearXy = FALSE;
    if (delta.x < 0x10 && delta.x > -0x10 && delta.y < 0x10 && delta.y > -0x10)
        nearXy = TRUE;
    if (nearXy && delta.z < 0x10 && delta.z > -0x10)
        result = TRUE;
    return result;
}
