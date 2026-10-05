#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const VecFx32 data_0205344c;
extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);

BOOL NormalizeUnlessDefault(VecFx32 *vec)
{
    BOOL isDefault = AreVecsWithinRange16(vec, &data_0205344c);
    if (isDefault == 0) {
        VEC_Normalize(vec, vec);
        return 0;
    }
    return 1;
}
