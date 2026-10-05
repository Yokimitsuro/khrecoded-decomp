#include "nitro/types.h"

extern void func_ov001_02079f80(void);
extern void UpdateMessageWindow(void); /* UpdateMessageWindow */
extern void CheckTimerExpired(void); /* CheckTimerExpired */
extern void func_ov001_0207a118(void); /* _fp_init */
extern void UpdateModeWidget(void); /* UpdateModeWidget */

void (*gMessageWindowStateHandlers[8])(void) = {
    NULL,
    NULL,
    NULL,
    func_ov001_02079f80,
    UpdateMessageWindow, /* UpdateMessageWindow */
    CheckTimerExpired, /* CheckTimerExpired */
    func_ov001_0207a118, /* _fp_init */
    UpdateModeWidget, /* UpdateModeWidget */
};
