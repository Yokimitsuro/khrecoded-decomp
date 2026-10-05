#include "nitro/types.h"

extern void func_ov038_020ba518(void); /* TryMarkSoundCtxActive */
extern void func_ov038_020ba54c(void); /* EnableOv038SoundCtx */
extern void func_ov038_020ba588(void);
extern void MarkSoundCtxRepeatIfReady(void); /* MarkSoundCtxRepeatIfReady */
extern void func_ov038_020ba5d4(void); /* DisableOv038Sound */
extern void func_ov038_020ba614(void);

void (*gResultsSoundStateHandlers[6])(void) = {
    func_ov038_020ba518, /* TryMarkSoundCtxActive */
    func_ov038_020ba54c, /* EnableOv038SoundCtx */
    func_ov038_020ba588,
    MarkSoundCtxRepeatIfReady, /* MarkSoundCtxRepeatIfReady */
    func_ov038_020ba5d4, /* DisableOv038Sound */
    func_ov038_020ba614,
};
