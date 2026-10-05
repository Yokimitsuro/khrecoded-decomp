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

void SetSceneFlag4000(void) {
    data_ov036_020c3940.work->flags |= 0x4000;
}
