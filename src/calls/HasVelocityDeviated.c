#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const VecFx32 data_0205344c;
extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);

BOOL HasVelocityDeviated(VecFx32 *velocity, VecFx32 *original)
{
    VecFx32 delta;
    VecFx32 originalDir;
    VecFx32 deltaDir;
    VecFx32 difference;
    VecFx32 originalUnit;
    VecFx32 deltaUnit;
    fx32 originalMag;

    if (!AreVecsWithinRange16(velocity, &data_0205344c)) {
        func_01ff9e3c(velocity, original, &difference);
        delta = difference;
        if (!AreVecsWithinRange16(&delta, &data_0205344c)) {
            VEC_Normalize(&delta, &deltaUnit);
            deltaDir = deltaUnit;
            originalMag = func_01ffaff4(original, &originalUnit);
            originalDir = originalUnit;
            if (VEC_DotProduct(&originalDir, &deltaDir) < 0xff0 || originalMag < VEC_Mag(velocity)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}
