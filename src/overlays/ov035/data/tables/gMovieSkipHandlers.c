#include "nitro/types.h"

extern void func_ov035_020ba594(void);
extern void LoadShadowModelAndReturnState2(void);
extern void func_ov035_020ba5e4(void);
extern void func_ov035_020ba610(void);
extern void PollOverlay40Phase(void); /* PollOverlay40Phase */
extern void FinishMovieSkip(void); /* FinishMovieSkip */
extern void func_ov035_020ba6c0(void);
extern void func_ov035_020ba6d8(void);
extern void func_ov035_020ba6e4(void);
extern void func_ov035_020ba760(void);

void (*gMovieSkipHandlers[10])(void) = {
    func_ov035_020ba594,
    LoadShadowModelAndReturnState2,
    func_ov035_020ba5e4,
    func_ov035_020ba610,
    PollOverlay40Phase, /* PollOverlay40Phase */
    FinishMovieSkip, /* FinishMovieSkip */
    func_ov035_020ba6c0,
    func_ov035_020ba6d8,
    func_ov035_020ba6e4,
    func_ov035_020ba760,
};
