#include "nitro/types.h"

typedef struct SceneState {
    u8 pad_00[0x6c];
    int phase;
} SceneState;

typedef struct SceneRef {
    SceneState *scene;
    int mode;
} SceneRef;

BOOL IsScenePhaseInterruptible(SceneRef *ref)
{
    if (ref->mode == 4) {
        switch (ref->scene->phase) {
        case 0:
        case 1:
        case 0x17:
        case 0x18:
            return FALSE;
        }
    }
    return TRUE;
}
