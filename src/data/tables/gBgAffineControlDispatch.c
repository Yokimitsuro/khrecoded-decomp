#include "nitro/types.h"

extern void Bg_SetMainBg2AffineControl(void); /* Bg_SetMainBg2AffineControl */
extern void Bg_SetMainBg3AffineControl(void); /* Bg_SetMainBg3AffineControl */
extern void Bg_SetSubBg2AffineControl(void); /* Bg_SetSubBg2AffineControl */
extern void Bg_SetSubBg3AffineControl(void); /* Bg_SetSubBg3AffineControl */

void (*const gBgAffineControlDispatch[8])(void) = {
    NULL,
    NULL,
    Bg_SetMainBg2AffineControl, /* Bg_SetMainBg2AffineControl */
    Bg_SetMainBg3AffineControl, /* Bg_SetMainBg3AffineControl */
    NULL,
    NULL,
    Bg_SetSubBg2AffineControl, /* Bg_SetSubBg2AffineControl */
    Bg_SetSubBg3AffineControl, /* Bg_SetSubBg3AffineControl */
};
