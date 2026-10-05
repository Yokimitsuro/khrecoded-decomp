#include "nitro/types.h"

extern void func_ov003_02064028(void); /* MovieScene_LoadBgChar */
extern void func_ov003_0206409c(void); /* MovieScene_LoadBgScreen */
extern void MovieScene_LoadSlotBuffer(void); /* MovieScene_LoadSlotBuffer */
extern void func_ov003_02064154(void); /* MovieScene_FadeInBgPlanes */
extern void func_ov003_02064230(void); /* MovieScene_FadeOutBgPlanes */
extern void func_ov003_020642fc(void);
extern void func_ov003_02064304(void); /* MovieScene_SetBgPriority */

void (*gMovieEventHandlers[7])(void) = {
    func_ov003_02064028, /* MovieScene_LoadBgChar */
    func_ov003_0206409c, /* MovieScene_LoadBgScreen */
    MovieScene_LoadSlotBuffer, /* MovieScene_LoadSlotBuffer */
    func_ov003_02064154, /* MovieScene_FadeInBgPlanes */
    func_ov003_02064230, /* MovieScene_FadeOutBgPlanes */
    func_ov003_020642fc,
    func_ov003_02064304, /* MovieScene_SetBgPriority */
};
