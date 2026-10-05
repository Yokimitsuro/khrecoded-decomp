#include "nitro/types.h"

extern void func_ov049_020c3520(void); /* InitSpinCameraOrbit */
extern void func_ov049_020c355c(void); /* InitFastSpinCameraOrbit */
extern void func_ov049_020c359c(void);
extern void func_ov049_020c35b8(void);
extern void func_ov049_020c35d4(void); /* InitRandomCameraSwing */
extern void func_ov049_020c3604(void); /* InitRandomCameraSway */

void (*gCameraMotionInitializers[6])(void) = {
    func_ov049_020c3520, /* InitSpinCameraOrbit */
    func_ov049_020c355c, /* InitFastSpinCameraOrbit */
    func_ov049_020c359c,
    func_ov049_020c35b8,
    func_ov049_020c35d4, /* InitRandomCameraSwing */
    func_ov049_020c3604, /* InitRandomCameraSway */
};
