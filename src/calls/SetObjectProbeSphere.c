#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct WorldObject {
    u8 pad_00[0x8];
    u16 flags;
    u8 pad_0A[0xb8 - 0xa];
    VecFx32 position;
    u8 pad_C4[0x11c - 0xc4];
    u8 shape[0x1a8 - 0x11c];
    u8 probe[0x18];
} WorldObject;

extern fx32 Surface_GetKindValue(void *shape);
extern BOOL ShadowVolume_Init(void *sphere, const VecFx32 *center, fx32 radius, int useLocal);

void SetObjectProbeSphere(WorldObject *object, BOOL enable, fx32 radius)
{
    if (enable) {
        if (radius == 0) {
            radius = (fx32)(((s64)Surface_GetKindValue(object->shape) * 0x1800 + 0x800) >> 12);
        }
        ShadowVolume_Init(object->probe, &object->position, radius, 0);
        object->flags |= 0x10;
    } else {
        object->flags &= ~0x10;
    }
}
