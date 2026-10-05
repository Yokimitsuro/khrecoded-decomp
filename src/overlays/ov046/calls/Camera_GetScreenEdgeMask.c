#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 NNS_G3dGlb_camPos;
extern VecFx32 NNS_G3dGlb_camTarget;
extern int NNS_G3dWorldPosToScrPos(const VecFx32 *position, int *screenX, int *screenY);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

BOOL Camera_GetScreenEdgeMask(u32 *edgeMask, const VecFx32 *position, int marginX, int marginY)
{
    int result;
    int screenX;
    int screenY;
    u32 mask = 0;
    VecFx32 toPosition;
    VecFx32 viewDirection;

    result = NNS_G3dWorldPosToScrPos(position, &screenX, &screenY);
    VEC_Subtract(position, &NNS_G3dGlb_camPos, &toPosition);
    VEC_Subtract(&NNS_G3dGlb_camTarget, &NNS_G3dGlb_camPos, &viewDirection);
    func_01ffaff4(&toPosition, &toPosition);
    func_01ffaff4(&viewDirection, &viewDirection);
    if (VEC_DotProduct(&viewDirection, &toPosition) < 0) {
        result = -1;
        screenX = -screenX;
        screenY = -screenY;
    }
    if (0xff - marginX < screenX) {
        mask |= 2;
        result = -1;
    }
    if (marginX > screenX) {
        mask |= 1;
        result = -1;
    }
    if (marginY > screenY) {
        mask |= 4;
        result = -1;
    }
    if (0xc0 - marginY < screenY) {
        mask |= 8;
        mask |= screenX < 0x80 ? 1 : 2;
        result = -1;
    }
    *edgeMask = mask;
    return result != -1;
}

