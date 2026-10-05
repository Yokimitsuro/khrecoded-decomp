#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FallingObject {
    u8 pad_00[8];
    void *manager;
    u8 pad_0C[0x60];
    fx32 maxDistance;
    VecFx32 position;
    VecFx32 velocity;
    u8 pad_88[4];
    fx32 height;
    u8 pad_90[8];
    fx32 fallStep;
} FallingObject;

extern void AdvanceSpawnerTimer(void *manager, FallingObject *object);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern BOOL ClampVecLength(VecFx32 *vec, fx32 maxLength);
extern fx32 VEC_Mag(const VecFx32 *v);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern int FX_Mul(int left, int right);
extern void func_ov001_02085348(FallingObject *object, int mode);

int StepFallingObject(FallingObject *object)
{
    VecFx32 next;

    AdvanceSpawnerTimer(object->manager, object);
    VEC_MultAdd(0x14, &object->velocity, &object->position, &next);
    object->position = next;
    object->position.y -= 0x52;
    ClampVecLength(&object->position, object->maxDistance);
    object->fallStep = FX_Mul(0x6488, FX_Div(VEC_Mag(&object->position), 0x82b2));
    object->height -= object->fallStep;
    func_ov001_02085348(object, 1);
    return 0;
}
