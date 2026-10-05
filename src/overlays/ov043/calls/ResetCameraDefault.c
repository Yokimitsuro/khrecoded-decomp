#include "nitro/types.h"

extern void *data_ov043_020bd2e0;
extern void InitCameraState_020bcbec(int arg, void *camera);

void ResetCameraDefault(void) {
    InitCameraState_020bcbec(0, data_ov043_020bd2e0);
}
