#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraTarget {
    u8 pad_00[0x38];
    VecFx32 focus;
    VecFx32 offset;
    u8 pad_50[0x30];
    int distance;
    u8 pad_84[0x18];
    int mode;
} CameraTarget;

extern CameraTarget *data_ov001_020a0514;

void SetCameraTargetParams(int mode, int distance, const VecFx32 *focus, const VecFx32 *offset)
{
    CameraTarget *target = data_ov001_020a0514;

    target->mode = mode;
    target->distance = distance;
    target->focus = *focus;
    target->offset = *offset;
}
