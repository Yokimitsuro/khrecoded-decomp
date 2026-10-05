#include "nitro/types.h"

extern void MovieScene_BeginDefaultFade(void); /* MovieScene_BeginDefaultFade */
extern void ResyncMovieSubtitleStream(void); /* ResyncMovieSubtitleStream */
extern void func_ov003_02064764(void);
extern void func_ov003_020647b8(void);
extern void func_ov003_020647f0(void);
extern void func_ov003_02064844(void); /* MsgQueue_GetHeap */
extern void func_ov003_02064850(void); /* thumbStep */

void (*gMovieScriptCommandHandlers[10])(void) = {
    MovieScene_BeginDefaultFade, /* MovieScene_BeginDefaultFade */
    NULL,
    ResyncMovieSubtitleStream, /* ResyncMovieSubtitleStream */
    NULL,
    func_ov003_02064764,
    NULL,
    func_ov003_020647b8,
    func_ov003_020647f0,
    func_ov003_02064844, /* MsgQueue_GetHeap */
    func_ov003_02064850, /* thumbStep */
};
