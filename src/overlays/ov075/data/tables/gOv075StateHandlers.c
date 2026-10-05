#include "nitro/types.h"

extern void func_ov075_020cc240(void);
extern void func_ov075_020cc570(void);
extern void func_ov075_020cc5c8(void);
extern void func_ov075_020cc3dc(void);
extern void func_ov075_020cc278(void);

void (*const gOv075StateHandlers[5])(void) = {
    func_ov075_020cc240,
    func_ov075_020cc570,
    func_ov075_020cc5c8,
    func_ov075_020cc3dc,
    func_ov075_020cc278,
};
