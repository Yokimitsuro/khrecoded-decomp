#include "nitro/types.h"

extern void func_ov001_0207bab4(void);
extern void UpdateAnimatedCounterHud(void);
extern void DrawCounterHudParts(void); /* DrawCounterHudParts */
extern void RefreshCounterDigits(void); /* RefreshCounterDigits */
extern void func_ov001_0207c2b0(void);
extern void RunLogoFadeSequence(void); /* RunLogoFadeSequence */
extern void func_ov001_0207ccb4(void);
extern void UpdateShortFadeSequence(void); /* UpdateShortFadeSequence */
extern void UpdateFadeSequence(void); /* UpdateFadeSequence */

void (*gCounterHudStateHandlers[6])(void) = {
    NULL,
    func_ov001_0207bab4,
    UpdateAnimatedCounterHud,
    DrawCounterHudParts, /* DrawCounterHudParts */
    RefreshCounterDigits, /* RefreshCounterDigits */
    func_ov001_0207c2b0,
};

void (*gFadeSequenceHandlers[5])(void) = {
    NULL,
    RunLogoFadeSequence, /* RunLogoFadeSequence */
    func_ov001_0207ccb4,
    UpdateShortFadeSequence, /* UpdateShortFadeSequence */
    UpdateFadeSequence, /* UpdateFadeSequence */
};
