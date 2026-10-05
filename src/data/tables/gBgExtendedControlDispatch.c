#include "nitro/types.h"

extern void Bg_SetMainBg2ExtControl(void); /* Bg_SetMainBg2ExtControl */
extern void Bg_SetMainBg3ExtControl(void); /* Bg_SetMainBg3ExtControl */
extern void Bg_SetSubBg2ExtControl(void); /* Bg_SetSubBg2ExtControl */
extern void Bg_SetSubBg3ExtControl(void); /* Bg_SetSubBg3ExtControl */

void (*const gBgExtendedControlDispatch[8])(void) = {
    NULL,
    NULL,
    Bg_SetMainBg2ExtControl, /* Bg_SetMainBg2ExtControl */
    Bg_SetMainBg3ExtControl, /* Bg_SetMainBg3ExtControl */
    NULL,
    NULL,
    Bg_SetSubBg2ExtControl, /* Bg_SetSubBg2ExtControl */
    Bg_SetSubBg3ExtControl, /* Bg_SetSubBg3ExtControl */
};
