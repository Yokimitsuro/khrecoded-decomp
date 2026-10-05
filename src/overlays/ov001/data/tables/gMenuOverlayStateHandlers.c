#include "nitro/types.h"

extern void func_ov001_0207abd8(void); /* _fp_init */
extern void func_ov001_0207abdc(void);
extern void func_ov001_0207ac18(void); /* StartMenuOverlayWindow */
extern void func_ov001_0207ac90(void); /* UpdateDisplayFadeState */
extern void StepSubScreenFadeIn(void); /* StepSubScreenFadeIn */
extern void StepSubScreenFadeIn_0207ad30(void); /* StepSubScreenFadeIn */
extern void func_ov001_0207ad5c(void); /* _fp_init */

void (*gMenuOverlayStateHandlers[7])(void) = {
    func_ov001_0207abd8, /* _fp_init */
    func_ov001_0207abdc,
    func_ov001_0207ac18, /* StartMenuOverlayWindow */
    func_ov001_0207ac90, /* UpdateDisplayFadeState */
    StepSubScreenFadeIn, /* StepSubScreenFadeIn */
    StepSubScreenFadeIn_0207ad30, /* StepSubScreenFadeIn */
    func_ov001_0207ad5c, /* _fp_init */
};
