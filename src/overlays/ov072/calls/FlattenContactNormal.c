#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 distance;
    VecFx32 normal;
} ContactPlane;

extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void SetPlaneNormalRescaled(ContactPlane *plane, const VecFx32 *normal);

BOOL FlattenContactNormal(void *contact, ContactPlane *plane)
{
    VecFx32 normal = plane->normal;
    fx32 vertical = normal.y;

    if (vertical < 0) {
        vertical = -vertical;
    }
    if (vertical > 0xff0) {
        return FALSE;
    }
    normal.y = 0;
    VEC_Normalize(&normal, &normal);
    SetPlaneNormalRescaled(plane, &normal);
    return TRUE;
}
