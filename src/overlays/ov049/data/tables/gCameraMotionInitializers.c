#include "nitro/types.h"

extern void InitSpinCameraOrbit(void); /* InitSpinCameraOrbit */
extern void InitFastSpinCameraOrbit(void); /* InitFastSpinCameraOrbit */
extern void func_ov049_020c359c(void);
extern void func_ov049_020c35b8(void);
extern void InitRandomCameraSwing(void); /* InitRandomCameraSwing */
extern void InitRandomCameraSway(void); /* InitRandomCameraSway */

void (*gCameraMotionInitializers[6])(void) = {
    InitSpinCameraOrbit, /* InitSpinCameraOrbit */
    InitFastSpinCameraOrbit, /* InitFastSpinCameraOrbit */
    func_ov049_020c359c,
    func_ov049_020c35b8,
    InitRandomCameraSwing, /* InitRandomCameraSwing */
    InitRandomCameraSway, /* InitRandomCameraSway */
};
