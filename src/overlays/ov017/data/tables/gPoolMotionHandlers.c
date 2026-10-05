#include "nitro/types.h"

extern void AdvancePool0Timer(void); /* AdvancePool0Timer */
extern void StepLinearPathMotion(void); /* StepLinearPathMotion */
extern void StepOrbitMotion(void); /* StepOrbitMotion */
extern void func_ov017_020a468c(void);
extern void UpdateOwnerFall(void); /* UpdateOwnerFall */

void (*const gPoolMotionHandlers[5])(void) = {
    AdvancePool0Timer, /* AdvancePool0Timer */
    StepLinearPathMotion, /* StepLinearPathMotion */
    StepOrbitMotion, /* StepOrbitMotion */
    func_ov017_020a468c,
    UpdateOwnerFall, /* UpdateOwnerFall */
};
