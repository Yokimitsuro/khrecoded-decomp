#include "nitro/types.h"

extern void func_ov000_02063108(void);
extern void func_ov000_02063170(void);
extern void func_ov000_020631d8(void);
extern void func_ov000_02063044(void);
extern void func_ov000_02063070(void);

void (*gTitleScreenOptionHandlers[4])(void) = {
    func_ov000_02063108,
    func_ov000_02063170,
    func_ov000_020631d8,
    NULL,
};

void (*gTitleScreenInputHandlers[2])(void) = {
    func_ov000_02063044,
    func_ov000_02063070,
};
