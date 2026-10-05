#include "nitro/types.h"

extern void func_ov085_020c165c(void);
extern void func_ov085_020c16ac(void);
extern void func_ov085_020c17e4(void);
extern void func_ov085_020c1848(void);
extern void func_ov085_020c18b4(void);

void (*gOv085StateHandlers[9])(void) = {
    func_ov085_020c165c,
    func_ov085_020c16ac,
    func_ov085_020c17e4,
    NULL,
    NULL,
    func_ov085_020c1848,
    func_ov085_020c18b4,
    NULL,
    func_ov085_020c17e4,
};
