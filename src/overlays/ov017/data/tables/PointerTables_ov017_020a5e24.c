#include "nitro/types.h"

extern void func_ov017_020a4290(void); /* Word_Clear */
extern void func_ov017_020a42d0(void); /* ComputePool1Progress */
extern void func_ov017_020a440c(void); /* ComputePool2Target */
extern void func_ov017_020a44f0(void); /* CopyPool3Entry */
extern void ResetFallTarget(void); /* ResetFallTarget */
extern void func_ov017_020a4c00(void);

void (*const gPoolValueHandlers[5])(void) = {
    func_ov017_020a4290, /* Word_Clear */
    func_ov017_020a42d0, /* ComputePool1Progress */
    func_ov017_020a440c, /* ComputePool2Target */
    func_ov017_020a44f0, /* CopyPool3Entry */
    ResetFallTarget, /* ResetFallTarget */
};

void (*const gPoolInitHandlers[4])(void) = {
    func_ov017_020a4c00,
    NULL,
    NULL,
    NULL,
};
