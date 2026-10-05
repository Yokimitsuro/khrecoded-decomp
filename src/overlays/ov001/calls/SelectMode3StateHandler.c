#include "nitro/types.h"

extern signed char func_ov001_02068084(void);
extern s32 func_ov007_020a08a4(u32 unused, void *obj);

void SelectMode3StateHandler(int stateId, u32 *outCleared, void *outHandler)
{
    void *handler = NULL;

    if ((func_ov001_02068084() == 3) && ((u32)(stateId - 0x1f) <= 1)) {
        handler = (void *)func_ov007_020a08a4;
    }
    if (outCleared != NULL) {
        *outCleared = 0;
    }
    if (outHandler != NULL) {
        *(void **)outHandler = handler;
    }
}
