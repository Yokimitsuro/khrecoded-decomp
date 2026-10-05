#include "nitro/types.h"

extern void func_ov001_0207bab4(void);
extern void func_ov001_0207bef4(void);
extern void func_ov001_0207c19c(void); /* DrawCounterHudParts */
extern void func_ov001_0207c1d0(void); /* RefreshCounterDigits */
extern void func_ov001_0207c2b0(void);
extern void func_ov001_0207cbd8(void); /* RunLogoFadeSequence */
extern void func_ov001_0207ccb4(void);
extern void func_ov001_0207d074(void); /* UpdateShortFadeSequence */
extern void func_ov001_0207d0e0(void); /* UpdateFadeSequence */

void (*gCounterHudStateHandlers[6])(void) = {
    NULL,
    func_ov001_0207bab4,
    func_ov001_0207bef4,
    func_ov001_0207c19c, /* DrawCounterHudParts */
    func_ov001_0207c1d0, /* RefreshCounterDigits */
    func_ov001_0207c2b0,
};

void (*gFadeSequenceHandlers[5])(void) = {
    NULL,
    func_ov001_0207cbd8, /* RunLogoFadeSequence */
    func_ov001_0207ccb4,
    func_ov001_0207d074, /* UpdateShortFadeSequence */
    func_ov001_0207d0e0, /* UpdateFadeSequence */
};
