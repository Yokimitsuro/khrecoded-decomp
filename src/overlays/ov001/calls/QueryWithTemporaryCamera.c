#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraState {
    u8 pad_00[0x84];
    int roll;
    u8 pad_88[0x18];
} CameraState;

extern CameraState *data_ov001_020a0514;

extern BOOL func_ov001_020645c8(u32 value);
extern void func_01ff8ad8(const void *src, void *dst, u32 size);
extern void SetFieldCameraTarget(int actorId, int mode, fx32 speed, int roll, VecFx32 *position, VecFx32 *rotation);
extern void *PXI_Init_02028dc0(void);
extern void *func_ov001_02088b48(int arg);
extern void *PXI_Init_02028dcc(void);

void *QueryWithTemporaryCamera(const VecFx32 *rotation, const VecFx32 *position, fx32 speed, int arg)
{
    CameraState *camera = data_ov001_020a0514;
    CameraState saved;
    VecFx32 pos;
    VecFx32 rot;
    void *result;

    if (!func_ov001_020645c8(0x3639)) {
        pos = *position;
        rot = *rotation;
        func_01ff8ad8(camera, &saved, sizeof(saved));
        pos.y += 0x1400;
        SetFieldCameraTarget(-1, 0, speed, camera->roll, &pos, &rot);
        PXI_Init_02028dc0();
        result = func_ov001_02088b48(arg);
        PXI_Init_02028dcc();
        func_01ff8ad8(&saved, camera, sizeof(saved));
    } else {
        result = NULL;
    }
    return result;
}
