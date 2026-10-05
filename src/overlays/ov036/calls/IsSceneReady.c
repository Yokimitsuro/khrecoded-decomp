#include "nitro/types.h"

typedef struct SceneWork {
    u8 unknown_00[6];
    u16 flags;
} SceneWork;

typedef struct SceneGlobals {
    void *unknown_00;
    SceneWork *work;
} SceneGlobals;

extern SceneGlobals data_ov036_020c3940;

BOOL IsSceneReady(void) {
    SceneWork *work = data_ov036_020c3940.work;

    if (work == NULL) {
        return FALSE;
    }
    return (work->flags & 1) == 0;
}
