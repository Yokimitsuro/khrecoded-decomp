#include "nitro/types.h"

extern void func_ov091_020c1780(void);
extern void RequestEntryTransitionIfIdle(void); /* RequestEntryTransitionIfIdle */
extern void func_ov091_020c17b0(void);

void (*const gReportTopStateHandlers[3])(void) = {
    func_ov091_020c1780,
    RequestEntryTransitionIfIdle, /* RequestEntryTransitionIfIdle */
    func_ov091_020c17b0,
};
