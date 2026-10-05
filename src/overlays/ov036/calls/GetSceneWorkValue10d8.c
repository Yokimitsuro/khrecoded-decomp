#include "nitro/types.h"

typedef struct SceneWork {
    u8 unknown_0000[0x10d8];
    int value;
} SceneWork;

typedef struct SceneGlobals {
    void *unknown_00;
    SceneWork *work;
} SceneGlobals;

extern SceneGlobals data_ov036_020c3940;

int GetSceneWorkValue10d8(void) {
    return data_ov036_020c3940.work->value;
}
