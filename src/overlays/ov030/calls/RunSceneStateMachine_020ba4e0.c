#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x18];
    int state;
} SceneState;

extern SceneState *data_ov030_020bd020;
extern int (*const gMovieSceneStateHandlers[])(void);

extern void ApplyOverlayScaleMode(int mode);
extern void func_ov030_020baab8(void);

int RunSceneStateMachine_020ba4e0(void) {
    int next;

    do {
        data_ov030_020bd020->flags &= 0x7fff;
        next = gMovieSceneStateHandlers[data_ov030_020bd020->state]();
        if (next >= 0) {
            data_ov030_020bd020->state = next;
        }
    } while (data_ov030_020bd020->flags & 0x8000);
    if (data_ov030_020bd020->flags & 8) {
        ApplyOverlayScaleMode(0);
    }
    if (data_ov030_020bd020->flags & 4) {
        func_ov030_020baab8();
    }
    return 0;
}
