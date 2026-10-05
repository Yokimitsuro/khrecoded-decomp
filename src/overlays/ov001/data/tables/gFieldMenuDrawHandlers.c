#include "nitro/types.h"

extern void func_ov001_020761a4(void);
extern void UpdateGaugeFrameState(void); /* UpdateGaugeFrameState */
extern void DrawFieldMenuSlots(void); /* DrawFieldMenuSlots */
extern void DrawFieldMenuSlotsAlt(void); /* DrawFieldMenuSlotsAlt */
extern void RefreshFieldMenuSlots(void); /* RefreshFieldMenuSlots */
extern void RefreshFieldMenuSlotsWrapped(void); /* RefreshFieldMenuSlotsWrapped */

void (*gFieldMenuDrawHandlers[6])(void) = {
    func_ov001_020761a4,
    UpdateGaugeFrameState, /* UpdateGaugeFrameState */
    DrawFieldMenuSlots, /* DrawFieldMenuSlots */
    DrawFieldMenuSlotsAlt, /* DrawFieldMenuSlotsAlt */
    RefreshFieldMenuSlots, /* RefreshFieldMenuSlots */
    RefreshFieldMenuSlotsWrapped, /* RefreshFieldMenuSlotsWrapped */
};
