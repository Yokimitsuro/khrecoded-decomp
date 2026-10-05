#include "nitro/types.h"

extern void func_01ffa5b0(void); /* func */
extern void func_01ffa680(void); /* EmitJointAnimationResult */

void (*gJointAnimationResultDispatch[3])(void) = {
    func_01ffa5b0, /* func */
    func_01ffa680, /* EmitJointAnimationResult */
    NULL,
};
