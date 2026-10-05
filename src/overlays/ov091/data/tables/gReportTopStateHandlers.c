#include "nitro/types.h"

extern void func_ov091_020c1780(void);
extern void RequestEntryTransitionIfIdle(void); /* RequestEntryTransitionIfIdle */
extern void RunIntroPopupStep(void);

void (*const gReportTopStateHandlers[3])(void) = {
    func_ov091_020c1780,
    RequestEntryTransitionIfIdle, /* RequestEntryTransitionIfIdle */
    RunIntroPopupStep,
};
