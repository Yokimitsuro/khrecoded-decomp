#include "nitro/types.h"

extern void func_ov001_02079f80(void);
extern void func_ov001_02079ff8(void); /* UpdateMessageWindow */
extern void func_ov001_0207a0e8(void); /* CheckTimerExpired */
extern void func_ov001_0207a118(void); /* _fp_init */
extern void func_ov001_0207a11c(void); /* UpdateModeWidget */

void (*gMessageWindowStateHandlers[8])(void) = {
    NULL,
    NULL,
    NULL,
    func_ov001_02079f80,
    func_ov001_02079ff8, /* UpdateMessageWindow */
    func_ov001_0207a0e8, /* CheckTimerExpired */
    func_ov001_0207a118, /* _fp_init */
    func_ov001_0207a11c, /* UpdateModeWidget */
};
