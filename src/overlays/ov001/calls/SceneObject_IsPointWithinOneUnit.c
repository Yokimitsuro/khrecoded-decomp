#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct SceneObject {
    u8 pad_00[0x40];
    VecFx32 position;
} SceneObject;

extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

BOOL SceneObject_IsPointWithinOneUnit(SceneObject *object, const VecFx32 *point)
{
    if (VEC_Distance(point, &object->position) < FX32_ONE) {
        return TRUE;
    }
    return FALSE;
}
