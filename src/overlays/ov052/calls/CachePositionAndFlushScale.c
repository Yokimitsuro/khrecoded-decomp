#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*ScaleCallback)(int entity, int delta);

extern void ComputeRootMotionDelta(int entity, VecFx32 *out);
extern int func_0202f4cc(void *anim, int arg);

void CachePositionAndFlushScale(int entity)
{
    VecFx32 position;
    ComputeRootMotionDelta(entity, &position);
    {
        fx32 x = position.x;
        fx32 z = position.z;
        fx32 y = position.y;
        *(fx32 *)(entity + 0x9c8) = x;
        *(fx32 *)(entity + 0x9cc) = y;
        *(fx32 *)(entity + 0x9d0) = z;
    }
    if (*(int *)(entity + 0x768) != 0) {
        int delta = func_0202f4cc((void *)(*(int *)(entity + 0x230) + 4), 0) - 0x1000;
        if (*(ScaleCallback *)(entity + 0x1fc) != NULL) {
            (*(ScaleCallback *)(entity + 0x1fc))(entity, delta);
        }
        *(int *)(entity + 0x768) = 0;
    }
}
