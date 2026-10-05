#include "nitro/types.h"

extern void func_ov022_020a93dc(void);
extern void func_ov022_020a93e0(void);

void (*gStreamStateHandlers[9])(void) = {
    func_ov022_020a93dc,
    func_ov022_020a93e0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
