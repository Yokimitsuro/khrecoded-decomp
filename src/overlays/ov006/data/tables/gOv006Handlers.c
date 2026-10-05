#include "nitro/types.h"

extern void func_ov006_020a0540(void);
extern void func_ov006_020a0604(void);

void (*gOv006Handlers[3])(void) = {
    func_ov006_020a0540,
    NULL,
    func_ov006_020a0604,
};
