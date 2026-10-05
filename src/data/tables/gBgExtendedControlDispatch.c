#include "nitro/types.h"

extern void func_0202b0c8(void); /* Bg_SetMainBg2ExtControl */
extern void func_0202b104(void); /* Bg_SetMainBg3ExtControl */
extern void func_0202b2a8(void); /* Bg_SetSubBg2ExtControl */
extern void func_0202b2e4(void); /* Bg_SetSubBg3ExtControl */

void (*const gBgExtendedControlDispatch[8])(void) = {
    NULL,
    NULL,
    func_0202b0c8, /* Bg_SetMainBg2ExtControl */
    func_0202b104, /* Bg_SetMainBg3ExtControl */
    NULL,
    NULL,
    func_0202b2a8, /* Bg_SetSubBg2ExtControl */
    func_0202b2e4, /* Bg_SetSubBg3ExtControl */
};
