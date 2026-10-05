#include "nitro/types.h"

extern void UpdateTimerHud(void);
extern void UpdateAnimatedCounterHud(void);
extern void DrawCounterHudParts(void); /* DrawCounterHudParts */
extern void RefreshCounterDigits(void); /* RefreshCounterDigits */
extern void UpdateCounterHudPanel(void);
extern void RunLogoFadeSequence(void); /* RunLogoFadeSequence */
extern void RunScoreTallySequence(void);
extern void UpdateShortFadeSequence(void); /* UpdateShortFadeSequence */
extern void UpdateFadeSequence(void); /* UpdateFadeSequence */

void (*gCounterHudStateHandlers[6])(void) = {
    NULL,
    UpdateTimerHud,
    UpdateAnimatedCounterHud,
    DrawCounterHudParts, /* DrawCounterHudParts */
    RefreshCounterDigits, /* RefreshCounterDigits */
    UpdateCounterHudPanel,
};

void (*gFadeSequenceHandlers[5])(void) = {
    NULL,
    RunLogoFadeSequence, /* RunLogoFadeSequence */
    RunScoreTallySequence,
    UpdateShortFadeSequence, /* UpdateShortFadeSequence */
    UpdateFadeSequence, /* UpdateFadeSequence */
};
