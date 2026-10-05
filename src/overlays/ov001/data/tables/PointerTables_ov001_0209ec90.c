#include "nitro/types.h"

extern void func_ov001_020702c0(void); /* UpdateHudSlideTween */
extern void func_ov001_0207031c(void);
extern void func_ov001_02070338(void); /* CheckSceneTimeout */
extern u8 data_ov001_0209ec60[];

void (*gHudSlideStateHandlers[5])(void) = {
    NULL,
    func_ov001_020702c0, /* UpdateHudSlideTween */
    func_ov001_0207031c,
    func_ov001_02070338, /* CheckSceneTimeout */
    func_ov001_020702c0, /* UpdateHudSlideTween */
};

void *gHudSlideData[2] = {
    data_ov001_0209ec60,
    data_ov001_0209ec60,
};
