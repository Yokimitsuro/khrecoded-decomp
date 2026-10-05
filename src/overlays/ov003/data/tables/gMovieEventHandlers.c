#include "nitro/types.h"

extern void MovieScene_LoadBgChar(void); /* MovieScene_LoadBgChar */
extern void MovieScene_LoadBgScreen(void); /* MovieScene_LoadBgScreen */
extern void MovieScene_LoadSlotBuffer(void); /* MovieScene_LoadSlotBuffer */
extern void func_ov003_02064154(void); /* MovieScene_FadeInBgPlanes */
extern void func_ov003_02064230(void); /* MovieScene_FadeOutBgPlanes */
extern void func_ov003_020642fc(void);
extern void MovieScene_SetBgPriority(void); /* MovieScene_SetBgPriority */

void (*gMovieEventHandlers[7])(void) = {
    MovieScene_LoadBgChar, /* MovieScene_LoadBgChar */
    MovieScene_LoadBgScreen, /* MovieScene_LoadBgScreen */
    MovieScene_LoadSlotBuffer, /* MovieScene_LoadSlotBuffer */
    func_ov003_02064154, /* MovieScene_FadeInBgPlanes */
    func_ov003_02064230, /* MovieScene_FadeOutBgPlanes */
    func_ov003_020642fc,
    MovieScene_SetBgPriority, /* MovieScene_SetBgPriority */
};
