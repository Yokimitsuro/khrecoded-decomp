#include "nitro/types.h"

extern void TryMarkSoundCtxActive(void); /* TryMarkSoundCtxActive */
extern void EnableOv038SoundCtx(void); /* EnableOv038SoundCtx */
extern void func_ov038_020ba588(void);
extern void MarkSoundCtxRepeatIfReady(void); /* MarkSoundCtxRepeatIfReady */
extern void DisableOv038Sound(void); /* DisableOv038Sound */
extern void func_ov038_020ba614(void);

void (*gResultsSoundStateHandlers[6])(void) = {
    TryMarkSoundCtxActive, /* TryMarkSoundCtxActive */
    EnableOv038SoundCtx, /* EnableOv038SoundCtx */
    func_ov038_020ba588,
    MarkSoundCtxRepeatIfReady, /* MarkSoundCtxRepeatIfReady */
    DisableOv038Sound, /* DisableOv038Sound */
    func_ov038_020ba614,
};
