#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
} Obj;

extern u8 func_ov001_02068084(void);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void SyncActorShapePosition(Obj *obj, VecFx32 *position);

void SetScaledPosition(Obj *obj, const VecFx32 *position)
{
    obj->position = *position;
    if (func_ov001_02068084() != 6) {
        ScaleVecFx32InPlace(&obj->position, FX_Div(0x1000, 0x1800));
    }
    SyncActorShapePosition(obj, &obj->position);
}
