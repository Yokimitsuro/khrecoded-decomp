#include "nitro/types.h"

extern void func_ov004_020622e4(void); /* PXI_Init */
extern void func_ov004_020622f0(void);
extern void func_ov004_02062530(void); /* UpdateScrollTextFadeOut */
extern void func_ov004_0206252c(void);

void (*gScrollTextHandlers[4])(void) = {
    func_ov004_020622e4, /* PXI_Init */
    func_ov004_020622f0,
    func_ov004_02062530, /* UpdateScrollTextFadeOut */
    func_ov004_0206252c,
};
