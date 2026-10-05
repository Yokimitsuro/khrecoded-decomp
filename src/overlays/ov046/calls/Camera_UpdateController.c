#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef void *(*CameraControllerFunc)(void *data, void *camera);

typedef struct CameraManager {
    u8 pad_00[0x38];
    VecFx32 eye;
    VecFx32 target;
    u8 pad_50[0x80 - 0x50];
    int type;
    u8 pad_84[0xdc - 0x84];
    u32 frameCount;
    u8 pad_e0[0xec - 0xe0];
    u32 prevState;
    u32 state;
    u8 pad_f4[0x138 - 0xf4];
    CameraControllerFunc controller;
    u8 controllerData[4];
} CameraManager;

typedef struct GameEntry {
    u8 pad_00[0x9ac];
    u64 flags;
} GameEntry;

extern CameraManager *data_ov046_020c3500;
extern u16 data_020604fc;
extern GameEntry *GetBoundedEntryField(int index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void Camera_BlendToVelocityAim(const VecFx32 *velocity, s32 curveType, fx32 duration);

int Camera_UpdateController(void)
{
    VecFx32 direction;
    VecFx32 normalized;
    VecFx32 diff;
    VecFx32 dirCopy;
    CameraControllerFunc next;

    data_ov046_020c3500->prevState = data_ov046_020c3500->state;
    if (data_ov046_020c3500->type != 0 && (GetBoundedEntryField(0)->flags & 0x100000000ULL)) {
        VEC_Subtract(&data_ov046_020c3500->target, &data_ov046_020c3500->eye, &diff);
        dirCopy = diff;
        VEC_Normalize(&dirCopy, &normalized);
        direction = normalized;
        Camera_BlendToVelocityAim(&direction, 0, FX32_ONE);
        data_ov046_020c3500->controller(data_ov046_020c3500->controllerData, data_ov046_020c3500);
    }
    next = data_ov046_020c3500->controller(data_ov046_020c3500->controllerData, data_ov046_020c3500);
    if (next != NULL) {
        data_ov046_020c3500->controller = next;
    }
    data_ov046_020c3500->frameCount = data_020604fc;
    return 0;
}





