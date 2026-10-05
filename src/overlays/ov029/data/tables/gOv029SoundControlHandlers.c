#include "nitro/types.h"

extern void func_ov029_020ba588(void);
extern void MarkSoundCtxActive(void); /* MarkSoundCtxActive */
extern void func_ov029_020ba5e8(void);
extern void func_ov029_020ba5fc(void);
extern void func_ov029_020ba690(void); /* EnableOv029Sound */
extern void HandleOverlayExitFlag(void); /* HandleOverlayExitFlag */
extern void func_ov029_020ba788(void); /* DisableOv029Sound */
extern void func_ov029_020ba844(void);

void (*gOv029SoundControlHandlers[8])(void) = {
    func_ov029_020ba588,
    MarkSoundCtxActive, /* MarkSoundCtxActive */
    func_ov029_020ba5e8,
    func_ov029_020ba5fc,
    func_ov029_020ba690, /* EnableOv029Sound */
    HandleOverlayExitFlag, /* HandleOverlayExitFlag */
    func_ov029_020ba788, /* DisableOv029Sound */
    func_ov029_020ba844,
};
