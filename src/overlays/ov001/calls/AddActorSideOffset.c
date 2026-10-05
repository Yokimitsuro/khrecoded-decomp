#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldActor {
    u8 pad_000[0x2a4];
    fx32 sideSpeed;
} FieldActor;

extern const VecFx32 data_ov001_020a0254;
extern fx32 func_ov001_02091840(FieldActor *actor);
extern int FX_Mul(int left, int right);
extern fx32 func_01ffaff4(const VecFx32 *source, VecFx32 *dest);
extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void AddActorSideOffset(FieldActor *actor, VecFx32 *position, const VecFx32 *direction)
{
    VecFx32 forward = *direction;
    VecFx32 side;
    fx32 scale = func_ov001_02091840(actor);

    if (actor->sideSpeed != 0) {
        scale = FX_Mul(actor->sideSpeed, scale);
        func_01ffaff4(&forward, &forward);
        func_01ff9ea8(&forward, &data_ov001_020a0254, &side);
        VEC_MultAdd(scale, &side, position, position);
    }
}
