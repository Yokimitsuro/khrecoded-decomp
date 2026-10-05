#include "nitro/types.h"

extern void func_ov093_020c2374(void);
extern void WaitForBrightnessReset(void); /* WaitForBrightnessReset */
extern void RunEntryUnlockSequence(void);
extern void func_ov093_020c2630(void);
extern void RunUnlockSequence(void);
extern void RunPrizeMessageSequence(void);
extern void func_ov093_020c2b20(void);

void (*const gTrophyReportStateHandlers[7])(void) = {
    func_ov093_020c2374,
    WaitForBrightnessReset, /* WaitForBrightnessReset */
    RunEntryUnlockSequence,
    func_ov093_020c2630,
    RunUnlockSequence,
    RunPrizeMessageSequence,
    func_ov093_020c2b20,
};
