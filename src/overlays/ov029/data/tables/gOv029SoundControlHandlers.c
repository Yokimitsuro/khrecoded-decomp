#include "nitro/types.h"

extern void func_ov029_020ba588(void);
extern void MarkSoundCtxActive(void); /* MarkSoundCtxActive */
extern void func_ov029_020ba5e8(void);
extern void FinishOv029MenuLoad(void);
extern void EnableOv029Sound(void); /* EnableOv029Sound */
extern void HandleOverlayExitFlag(void); /* HandleOverlayExitFlag */
extern void DisableOv029Sound(void); /* DisableOv029Sound */
extern void func_ov029_020ba844(void);

void (*gOv029SoundControlHandlers[8])(void) = {
    func_ov029_020ba588,
    MarkSoundCtxActive, /* MarkSoundCtxActive */
    func_ov029_020ba5e8,
    FinishOv029MenuLoad,
    EnableOv029Sound, /* EnableOv029Sound */
    HandleOverlayExitFlag, /* HandleOverlayExitFlag */
    DisableOv029Sound, /* DisableOv029Sound */
    func_ov029_020ba844,
};
