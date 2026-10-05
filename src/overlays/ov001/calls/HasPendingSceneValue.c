#include "nitro/types.h"

typedef struct Scene {
    u8 pad_000[0x2e4];
    s64 pendingValue;
} Scene;

typedef struct SceneGlobals {
    int allocEnabled;
    Scene *scene;
} SceneGlobals;

extern SceneGlobals data_ov001_020a04c4;

BOOL HasPendingSceneValue(void)
{
    if (data_ov001_020a04c4.scene->pendingValue != 0) {
        return TRUE;
    }
    return FALSE;
}
