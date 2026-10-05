#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int NormalizeIfShort(VecFx32 *vec);

void NormalizeVecFx32Out(VecFx32 *out, const VecFx32 *src)
{
    VecFx32 tmp = *src;
    NormalizeIfShort(&tmp);
    *out = tmp;
}
