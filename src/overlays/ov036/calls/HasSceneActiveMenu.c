#include "nitro/types.h"

typedef struct SceneWork {
    u8 unknown_000[0xc7c];
    void *activeMenu;
} SceneWork;

typedef struct SceneGlobals {
    void *unknown_00;
    SceneWork *work;
} SceneGlobals;

extern SceneGlobals data_ov036_020c3940;

BOOL HasSceneActiveMenu(void) {
    return data_ov036_020c3940.work->activeMenu != NULL;
}
