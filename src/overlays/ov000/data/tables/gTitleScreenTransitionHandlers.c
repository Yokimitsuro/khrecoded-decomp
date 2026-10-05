#include "nitro/types.h"

extern void func_ov000_020630a4(void);
extern void func_ov000_020630d4(void);

void (*gTitleScreenTransitionHandlers[2])(void) = {
    func_ov000_020630a4,
    func_ov000_020630d4,
};
