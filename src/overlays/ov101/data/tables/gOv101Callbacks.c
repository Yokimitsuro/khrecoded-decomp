#include "nitro/types.h"

extern void func_ov101_020c17e0(void);
extern void func_ov101_020c17e4(void);

void (*const gOv101Callbacks[2])(void) = {
    func_ov101_020c17e0,
    func_ov101_020c17e4,
};
