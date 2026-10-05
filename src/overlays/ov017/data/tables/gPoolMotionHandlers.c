#include "nitro/types.h"

extern void func_ov017_020a4298(void); /* AdvancePool0Timer */
extern void func_ov017_020a4318(void); /* StepLinearPathMotion */
extern void func_ov017_020a4440(void); /* StepOrbitMotion */
extern void func_ov017_020a468c(void);
extern void func_ov017_020a48ec(void); /* UpdateOwnerFall */

void (*const gPoolMotionHandlers[5])(void) = {
    func_ov017_020a4298, /* AdvancePool0Timer */
    func_ov017_020a4318, /* StepLinearPathMotion */
    func_ov017_020a4440, /* StepOrbitMotion */
    func_ov017_020a468c,
    func_ov017_020a48ec, /* UpdateOwnerFall */
};
