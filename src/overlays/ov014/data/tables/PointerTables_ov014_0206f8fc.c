#include "nitro/types.h"

extern void func_ov014_0206d2e0(void);
extern void func_ov014_0206d2e4(void);
extern void func_ov014_0206d2e8(void);
extern void func_ov014_0206e84c(void);
extern void func_ov014_0206e850(void);
extern void func_ov014_0206e86c(void); /* UpdatePanelCloseStep */
extern void func_ov014_0206e8fc(void);
extern void func_ov014_0206d25c(void); /* UpdatePanelOpenStep */

void (*gPanelLifecycleHandlers[7])(void) = {
    func_ov014_0206d2e0,
    func_ov014_0206d2e4,
    func_ov014_0206d2e8,
    func_ov014_0206e84c,
    func_ov014_0206e850,
    func_ov014_0206e86c, /* UpdatePanelCloseStep */
    func_ov014_0206e8fc,
};

void (*gPanelOpenStepHandler[1])(void) = {
    func_ov014_0206d25c, /* UpdatePanelOpenStep */
};
