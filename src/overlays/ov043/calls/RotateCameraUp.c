#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov043_020bd2e0;
extern VecFx32 *GetSubStruct1C(void);
extern void RotateVectorAroundAxis(VecFx32 *vec, const VecFx32 *axis, s32 angle);

void RotateCameraUp(s32 angle) {
    u8 *camera;
    if (angle == 0) {
        return;
    }
    camera = data_ov043_020bd2e0;
    RotateVectorAroundAxis((VecFx32 *)(camera + 0x2c), GetSubStruct1C(), angle);
}
