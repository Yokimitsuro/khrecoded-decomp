#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s32 func_ov031_020bc720(void);
extern BOOL IsWithinPlaneSet_0203ebdc(VecFx32 *point, s32 threshold);

BOOL IsPointInViewDepth(VecFx32 *point, s32 threshold) {
    if (point->z < -(threshold + func_ov031_020bc720())) {
        return FALSE;
    }
    return IsWithinPlaneSet_0203ebdc(point, threshold);
}
