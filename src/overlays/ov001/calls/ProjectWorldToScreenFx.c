#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int NNS_G3dWorldPosToScrPos(const VecFx32 *world, int *x, int *y);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern VecFx32 NNS_G3dGlb_camPos;
extern VecFx32 NNS_G3dGlb_camTarget;

int ProjectWorldToScreenFx(const VecFx32 *world, fx32 *screen)
{
    VecFx32 toWorld;
    VecFx32 viewDir;
    int x;
    int y;
    int result;
    VecFx32 *cameraPos = &NNS_G3dGlb_camPos;

    result = NNS_G3dWorldPosToScrPos(world, &x, &y);
    y -= 8;
    if (result != -1) {
        VEC_Subtract(world, cameraPos, &toWorld);
        VEC_Subtract(&NNS_G3dGlb_camTarget, cameraPos, &viewDir);
        if (toWorld.x != 0 || toWorld.y != 0 || toWorld.z != 0) {
            VEC_Normalize(&toWorld, &toWorld);
        }
        if (viewDir.x != 0 || viewDir.y != 0 || viewDir.z != 0) {
            VEC_Normalize(&viewDir, &viewDir);
        }
        if (VEC_DotProduct(&viewDir, &toWorld) < 0) {
            result = -1;
        }
    }
    screen[0] = x << 12;
    screen[1] = y << 12;
    return result;
}
