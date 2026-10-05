#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x18];
    int state;
} SceneState;

extern SceneState *data_ov028_020bb3a0;
extern int (*const gSceneStateHandlers[])(void);

extern void func_ov028_020bae88(s32 mode);
extern void func_ov028_020bae68(void);

int RunSceneStateMachine(void) {
    int next;

    do {
        data_ov028_020bb3a0->flags &= 0x7fff;
        next = gSceneStateHandlers[data_ov028_020bb3a0->state]();
        if (next >= 0) {
            data_ov028_020bb3a0->state = next;
        }
    } while (data_ov028_020bb3a0->flags & 0x8000);
    if (data_ov028_020bb3a0->flags & 8) {
        func_ov028_020bae88(0);
    }
    if (data_ov028_020bb3a0->flags & 4) {
        func_ov028_020bae68();
    }
    return 0;
}
