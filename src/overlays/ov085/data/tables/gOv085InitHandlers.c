#include "nitro/types.h"

extern void func_ov085_020bf810(void);
extern void func_ov085_020c01d8(void);

void (*gOv085InitHandlers[2])(void) = {
    func_ov085_020bf810,
    func_ov085_020c01d8,
};
