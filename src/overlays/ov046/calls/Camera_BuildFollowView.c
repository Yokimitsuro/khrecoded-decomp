#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0xe4];
    int mode;
} CameraManager;

typedef struct CameraView CameraView;

extern CameraManager *data_ov046_020c3500;
extern const s16 data_02053580[];
extern int GetBiasAdjustedField(int playerIndex);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern void func_ov046_020c17bc(CameraView *view, u16 heading);

void Camera_BuildFollowView(CameraView *view)
{
    int heading;
    int index;

    if (data_ov046_020c3500->mode != 0x13 && data_ov046_020c3500->mode != 0x15) {
        heading = GetBiasAdjustedField(0);
    } else {
        heading = 0;
    }
    index = (u16)heading >> 4;
    func_ov046_020c17bc(view, FX_Atan2Idx(-data_02053580[(0x400 - index) & 0xfff], -data_02053580[index]));
}
