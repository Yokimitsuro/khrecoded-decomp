#include "nitro/types.h"

extern void func_01ffa5b0(void); /* func */
extern void EmitJointAnimationResult(void); /* EmitJointAnimationResult */

void (*gJointAnimationResultDispatch[3])(void) = {
    func_01ffa5b0, /* func */
    EmitJointAnimationResult, /* EmitJointAnimationResult */
    NULL,
};
