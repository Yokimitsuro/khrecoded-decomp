#include "nitro/types.h"

extern void func_ov093_020c2374(void);
extern void WaitForBrightnessReset(void); /* WaitForBrightnessReset */
extern void func_ov093_020c23c8(void);
extern void func_ov093_020c2630(void);
extern void func_ov093_020c2870(void);
extern void func_ov093_020c2970(void);
extern void func_ov093_020c2b20(void);

void (*const gTrophyReportStateHandlers[7])(void) = {
    func_ov093_020c2374,
    WaitForBrightnessReset, /* WaitForBrightnessReset */
    func_ov093_020c23c8,
    func_ov093_020c2630,
    func_ov093_020c2870,
    func_ov093_020c2970,
    func_ov093_020c2b20,
};
