#include "nitro/types.h"

extern void func_ov003_020647a8(void); /* MovieScene_BeginDefaultFade */
extern void func_ov003_02064818(void); /* ResyncMovieSubtitleStream */
extern void func_ov003_02064764(void);
extern void func_ov003_020647b8(void);
extern void func_ov003_020647f0(void);
extern void func_ov003_02064844(void); /* MsgQueue_GetHeap */
extern void func_ov003_02064850(void); /* thumbStep */

void (*gMovieScriptCommandHandlers[10])(void) = {
    func_ov003_020647a8, /* MovieScene_BeginDefaultFade */
    NULL,
    func_ov003_02064818, /* ResyncMovieSubtitleStream */
    NULL,
    func_ov003_02064764,
    NULL,
    func_ov003_020647b8,
    func_ov003_020647f0,
    func_ov003_02064844, /* MsgQueue_GetHeap */
    func_ov003_02064850, /* thumbStep */
};
