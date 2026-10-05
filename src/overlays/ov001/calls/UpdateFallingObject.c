#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FallingObject
{
    u8 pad_00[0x8];
    void *manager;
    u8 pad_0C[0x34];
    VecFx32 position;
    u8 pad_4C[0x24];
    VecFx32 velocity;
    u8 pad_7C[0x10];
    fx32 unk_8C;
    u8 pad_90[0x8];
    fx32 unk_98;
} FallingObject;

extern void func_ov001_02085054(void *manager, FallingObject *object);
extern int FX_Mul(int left, int right);
extern void func_ov001_02085348(FallingObject *object, int mode);
extern void func_ov001_02084f60(FallingObject *object);

int UpdateFallingObject(FallingObject *object)
{
    func_ov001_02085054(object->manager, object);
    object->velocity.x = FX_Mul(object->velocity.x, 0xF33);
    object->velocity.z = FX_Mul(object->velocity.z, 0xF33);
    object->velocity.y -= 0x7B;
    object->unk_8C -= object->unk_98;
    func_ov001_02085348(object, 0);
    if (object->position.y < -0x14000)
        func_ov001_02084f60(object);
    return 0;
}
