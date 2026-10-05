#include "nitro/types.h"

extern void func_ov001_020761a4(void);
extern void func_ov001_020761d8(void); /* UpdateGaugeFrameState */
extern void func_ov001_0207621c(void); /* DrawFieldMenuSlots */
extern void func_ov001_0207639c(void); /* DrawFieldMenuSlotsAlt */
extern void func_ov001_0207651c(void); /* RefreshFieldMenuSlots */
extern void func_ov001_020767ec(void); /* RefreshFieldMenuSlotsWrapped */

void (*gFieldMenuDrawHandlers[6])(void) = {
    func_ov001_020761a4,
    func_ov001_020761d8, /* UpdateGaugeFrameState */
    func_ov001_0207621c, /* DrawFieldMenuSlots */
    func_ov001_0207639c, /* DrawFieldMenuSlotsAlt */
    func_ov001_0207651c, /* RefreshFieldMenuSlots */
    func_ov001_020767ec, /* RefreshFieldMenuSlotsWrapped */
};
