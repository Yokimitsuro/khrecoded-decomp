#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const VecFx32 data_0205344c;
extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);

BOOL IsNearOrigin(const VecFx32 *point)
{
    return AreVecsWithinRange16(point, &data_0205344c);
}
