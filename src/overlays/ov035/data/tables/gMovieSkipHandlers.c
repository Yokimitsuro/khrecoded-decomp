#include "nitro/types.h"

extern void func_ov035_020ba594(void);
extern void func_ov035_020ba5d8(void);
extern void func_ov035_020ba5e4(void);
extern void func_ov035_020ba610(void);
extern void func_ov035_020ba648(void); /* PollOverlay40Phase */
extern void func_ov035_020ba688(void); /* FinishMovieSkip */
extern void func_ov035_020ba6c0(void);
extern void func_ov035_020ba6d8(void);
extern void func_ov035_020ba6e4(void);
extern void func_ov035_020ba760(void);

void (*gMovieSkipHandlers[10])(void) = {
    func_ov035_020ba594,
    func_ov035_020ba5d8,
    func_ov035_020ba5e4,
    func_ov035_020ba610,
    func_ov035_020ba648, /* PollOverlay40Phase */
    func_ov035_020ba688, /* FinishMovieSkip */
    func_ov035_020ba6c0,
    func_ov035_020ba6d8,
    func_ov035_020ba6e4,
    func_ov035_020ba760,
};
