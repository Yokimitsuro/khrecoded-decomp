#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 PickPerpendicularAxis(const VecFx32 *vec);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline VecFx32 Cross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_CrossProduct(a, b, &result);
    return result;
}

static inline VecFx32 CrossWithAxis(const VecFx32 *vec)
{
    VecFx32 axis;

    axis = PickPerpendicularAxis(vec);
    return Cross(vec, &axis);
}

VecFx32 GetPerpendicularVector(const VecFx32 *vec)
{
    if (vec->x == 0 && vec->y == 0 && vec->z == 0) {
        VecFx32 fallback = PickPerpendicularAxis(vec);
        return CrossWithAxis(&fallback);
    }
    return CrossWithAxis(vec);
}
