#include "nitro/types.h"

extern void func_0202b050(void); /* Bg_SetMainBg2AffineControl */
extern void func_0202b08c(void); /* Bg_SetMainBg3AffineControl */
extern void func_0202b230(void); /* Bg_SetSubBg2AffineControl */
extern void func_0202b26c(void); /* Bg_SetSubBg3AffineControl */

void (*const gBgAffineControlDispatch[8])(void) = {
    NULL,
    NULL,
    func_0202b050, /* Bg_SetMainBg2AffineControl */
    func_0202b08c, /* Bg_SetMainBg3AffineControl */
    NULL,
    NULL,
    func_0202b230, /* Bg_SetSubBg2AffineControl */
    func_0202b26c, /* Bg_SetSubBg3AffineControl */
};
