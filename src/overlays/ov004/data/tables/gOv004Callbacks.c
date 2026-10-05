#include "nitro/types.h"

extern void func_ov004_02061694(void);
extern void func_ov004_0206223c(void);
extern void func_ov004_020616b4(void);
extern void func_ov004_02062250(void);

void (*const gOv004Callbacks[4])(void) = {
    func_ov004_02061694,
    func_ov004_0206223c,
    func_ov004_020616b4,
    func_ov004_02062250,
};
