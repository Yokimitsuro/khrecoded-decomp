#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x84];
    s32 busy;
} SceneContext;

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x28];
    s32 stateIndex;
} SceneState;

typedef struct {
    SceneContext *context;
    SceneState *scene;
} Ov032Globals;

typedef s32 (*SceneStateHandler)(void);

extern Ov032Globals data_ov032_020c0080;
extern SceneStateHandler gGroupActionStateHandlers[];
extern void func_ov032_020bb388(s32 keepAlive);
extern void func_ov032_020bb36c(void);

s32 RunSceneStateMachine_020ba7b0(void) {
    s32 nextState;
    if (data_ov032_020c0080.context->busy != 0 && !(data_ov032_020c0080.scene->flags & 2)) {
        return 0;
    }
    do {
        data_ov032_020c0080.scene->flags &= 0x7fff;
        nextState = gGroupActionStateHandlers[data_ov032_020c0080.scene->stateIndex]();
        if (nextState >= 0) {
            data_ov032_020c0080.scene->stateIndex = nextState;
        }
    } while (data_ov032_020c0080.scene->flags & 0x8000);
    if (data_ov032_020c0080.scene->flags & 8) {
        func_ov032_020bb388(0);
    }
    if (data_ov032_020c0080.scene->flags & 4) {
        func_ov032_020bb36c();
    }
    return 0;
}
