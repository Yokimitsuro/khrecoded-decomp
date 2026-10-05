#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 distance;
    VecFx32 normal;
} ContactPlane;

extern BOOL IsFacingContactNormal(void *contact, VecFx32 *normal);
extern void SetPlaneNormalRescaled(ContactPlane *plane, const VecFx32 *normal);
extern const VecFx32 data_ov072_020d9bdc;

BOOL SnapContactNormalUp(void *contact, ContactPlane *plane)
{
    if (!IsFacingContactNormal(contact, &plane->normal)) {
        return FALSE;
    }
    if (plane->normal.y < 0x165) {
        return FALSE;
    }
    SetPlaneNormalRescaled(plane, &data_ov072_020d9bdc);
    return TRUE;
}
