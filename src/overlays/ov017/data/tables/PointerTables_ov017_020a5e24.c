#include "nitro/types.h"

extern void func_ov017_020a4290(void); /* Word_Clear */
extern void ComputePool1Progress(void); /* ComputePool1Progress */
extern void ComputePool2Target(void); /* ComputePool2Target */
extern void CopyPool3Entry(void); /* CopyPool3Entry */
extern void ResetFallTarget(void); /* ResetFallTarget */
extern void func_ov017_020a4c00(void);

void (*const gPoolValueHandlers[5])(void) = {
    func_ov017_020a4290, /* Word_Clear */
    ComputePool1Progress, /* ComputePool1Progress */
    ComputePool2Target, /* ComputePool2Target */
    CopyPool3Entry, /* CopyPool3Entry */
    ResetFallTarget, /* ResetFallTarget */
};

void (*const gPoolInitHandlers[4])(void) = {
    func_ov017_020a4c00,
    NULL,
    NULL,
    NULL,
};
