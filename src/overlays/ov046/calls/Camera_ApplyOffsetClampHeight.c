#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x14];
    VecFx32 target;
    VecFx32 position;
    u8 pad_2C[0xc];
    VecFx32 basePosition;
    VecFx32 baseTarget;
    u8 pad_50[0x48];
    VecFx32 offset;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_ov001_02067ed4(void);
extern s32 func_ov001_0206805c(int index);

void Camera_ApplyOffsetClampHeight(void)
{
    VEC_Add(&data_ov046_020c3500->basePosition, &data_ov046_020c3500->offset, &data_ov046_020c3500->position);
    VEC_Add(&data_ov046_020c3500->baseTarget, &data_ov046_020c3500->offset, &data_ov046_020c3500->target);
    if (func_ov001_02067ed4() != -1) {
        s32 limit = func_ov001_0206805c(func_ov001_02067ed4());
        data_ov046_020c3500->position.y = (data_ov046_020c3500->position.y <= limit) ? data_ov046_020c3500->position.y : limit;
    }
}
